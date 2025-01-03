#define FASTLED_INTERNAL //remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#include <FastLED.h>
#include <ArduinoJson.h> // Ensure ArduinoJson library is included
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include "tusb.h"
#include "USB.h"
#include "USBHIDMouse.h"
#include "ConfigSecure.h"
//#include "ConfigExample.h"
#include "ConfigPins.h"

// Define custom USB product name, manufacturer, and serial number
#define CUSTOM_PRODUCT_NAME "Demo_Usb"
#define CUSTOM_MANUFACTURER "DemoTxt"
#define CUSTOM_SERIAL_NUMBER "1234567890"

using namespace websockets;

// USB peripherals
USBHIDMouse Mouse;

// Setup leds
CRGB leds;

// TFT display instance
TFT_eSPI tft = TFT_eSPI();

// WebSocket client instance
WebsocketsClient client;

// Feature states - initialized to off
bool TFTEnabled;      // Defaults to false
bool LEDEnabled;      // Defaults to false
bool KeyboardEnabled; // Defaults to false
bool MouseEnabled;    // Defaults to false
bool JigglerEnabled = true; // Defaults to false

// Configuration for Jiggler interval (in seconds)
const unsigned long jigglerInterval = 60; // Adjust the interval as needed
unsigned long lastJigglerTime = 0;       // Tracks the last time the mouse was moved

// Custom string descriptor callback
extern "C" const uint16_t* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    static uint16_t descriptor[32]; // Buffer for UTF-16 string
    const char* string = nullptr;

    switch (index) {
        case 0: // Language ID
            descriptor[0] = (TUSB_DESC_STRING << 8) | (2 * 1 + 2); // Length of descriptor and type
            descriptor[1] = 0x0409; // English (United States) language ID
            return descriptor;
        case 1: // Product Name
            string = CUSTOM_PRODUCT_NAME;
            break;
        case 2: // Manufacturer Name
            string = CUSTOM_MANUFACTURER;
            break;
        case 3: // Serial Number
            string = CUSTOM_SERIAL_NUMBER;
            break;
        default:
            return nullptr;
    }

    // Convert ASCII to UTF-16
    if (string) {
        size_t len = strlen(string);
        if (len > 31) len = 31; // Limit to 31 characters
        descriptor[0] = (TUSB_DESC_STRING << 8) | (2 * len + 2); // Length and type
        for (size_t i = 0; i < len; i++) {
            descriptor[i + 1] = string[i];
        }
        return descriptor;
    }

    return nullptr;
}

// Function to perform mouse jiggle
void performMouseJiggle(int repeatAmount) {
    setLEDState(CRGB::Black);
    for (int i = 0; i < repeatAmount; i++) {
        setLEDState(CRGB::Blue);
        Mouse.move(JIGGLE_AMOUNT, 0);
        delay(JIGGLE_DELAY);
        Mouse.move(-JIGGLE_AMOUNT, 0);
        delay(JIGGLE_FLASH_DELAY);
        setLEDState(CRGB::Green);
    }
}

// Function to check mouse jiggle
void checkJiggle() {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = (currentTime - lastJigglerTime) / 1000; // Elapsed time in seconds

    if (JigglerEnabled) {
        if (elapsedTime >= jigglerInterval) {
            performMouseJiggle(2); //Repeate the jiggle
            lastJigglerTime = currentTime; // Update the last jiggle time
            printMsg("Timmer: reset");
        } else {
            // Calculate and print remaining time until the next jiggle
            unsigned long remainingTime = jigglerInterval - elapsedTime;
            String message = "Timmer:" + String(remainingTime);
            printMsg(message.c_str());
            delay(1000);
        }
    }
}

// Function to control the LED
void setLEDState(CRGB color) {
    if (ENABLE_LED) {
        leds = color;
        FastLED.setBrightness(10);
        FastLED.show();
    }
}

// Function to print messages to TFT and Serial Monitor based on flags
void printMsg(const char* message) {
    if (DEBUG_TFT) {
        tft.fillScreen(TFT_BLACK); // Clear the screen
        tft.setCursor(10, 10);     // Set cursor position
        tft.println(message);      // Print message to TFT
    }

    if (DEBUG_SERIAL) {
        Serial.println(message); // Print message to Serial Monitor
    }
}

// Callback for WebSocket messages
void onMessageCallback(WebsocketsMessage message) {
    StaticJsonDocument<256> doc; // Allocate a JSON document

    // Parse the JSON string
    DeserializationError error = deserializeJson(doc, message.data());
    if (error) {
        printMsg("Failed to parse JSON message");
        return;
    }

    // Extract fields from the JSON
    const char* deviceId = doc["DeviceId"];
    int action = doc["Action"];
    bool isEnabled = doc["IsEnabled"];
    const char* actionMessage = doc["Message"];

    // Ensure this message is for this device or for all devices
    if (String(deviceId) != "ALL" && String(deviceId) != WiFi.macAddress()) {
        return; // Ignore messages not intended for this device
    }

    // Log the message regardless of the action
    printMsg(actionMessage);

    // Handle actions based on the type
    switch (action) {
        case 0: // TFT
            TFTEnabled = isEnabled;
            if (TFTEnabled) {
                printMsg(actionMessage); // Display the message on TFT
            } else {
                tft.fillScreen(TFT_BLACK); // Clear TFT when disabled
            }
            break;

        case 1: // LED
            LEDEnabled = isEnabled;
            if (LEDEnabled) {
                // Change LED color based on the message
                if (strcmp(actionMessage, "Red") == 0) {
                    setLEDState(CRGB::Red);
                } else if (strcmp(actionMessage, "Green") == 0) {
                    setLEDState(CRGB::Green);
                } else if (strcmp(actionMessage, "Blue") == 0) {
                    setLEDState(CRGB::Blue);
                } else if (strcmp(actionMessage, "Yellow") == 0) {
                    setLEDState(CRGB::Yellow);
                } else if (strcmp(actionMessage, "White") == 0) {
                    setLEDState(CRGB::White);
                } else {
                    printMsg("Unknown LED color");
                }
            } else {
                setLEDState(CRGB::Black); // Turn off LED when disabled
            }
            break;

        case 2: // Keyboard
            KeyboardEnabled = isEnabled;
            printMsg(KeyboardEnabled ? "Keyboard Enabled" : "Keyboard Disabled");
            break;

        case 3: // Mouse
            MouseEnabled = isEnabled;
            printMsg(MouseEnabled ? "Mouse Enabled" : "Mouse Disabled");
            break;

        case 4: // Jiggler
            JigglerEnabled = isEnabled;

            if(JigglerEnabled){
                lastJigglerTime = millis(); // Reset the timer when enabling the jiggler
                //Mouse.move(100, 0);  // Wake computer up
                //Mouse.move(-100, 0);
                performMouseJiggle(3); // Perform a jiggle
                //setLEDState(CRGB::Green);
            }
            else{
                setLEDState(CRGB::Black);
            }

            printMsg(JigglerEnabled ? "Jiggler Enabled" : "Jiggler Disabled");
            break;

        default:
            printMsg("Unknown action");
            break;
    }
}

// Callback for WebSocket events
void onEventsCallback(WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
        printMsg("WS Connected");
        setLEDState(CRGB::Green); // Set LED to green on connection
    } else if (event == WebsocketsEvent::ConnectionClosed) {
        printMsg("WS Disconnected");
        setLEDState(CRGB::Red); // Set LED to red on disconnection
    } else if (event == WebsocketsEvent::GotPing) {
        printMsg("Ping Received");
    } else if (event == WebsocketsEvent::GotPong) {
        printMsg("Pong Received");
    } else {
        printMsg("Unknown WebSocket Event");
    }
}

// Function to connect to WiFi
void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    printMsg("Connecting to WiFi...");
    setLEDState(CRGB::Yellow); // Set LED to yellow while connecting
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printMsg("Connecting..."); // Display connecting status repeatedly
    }
    printMsg("WiFi Connected");
    setLEDState(CRGB::Green); // Set LED to green once connected
}

// Function to connect to WebSocket
void connectToWebSocket() {
    printMsg("Connecting to WS...");
    if (client.connect(WEBSOCKETS_URL)) {
        printMsg("WS Connected");
        setLEDState(CRGB::Green); // Set LED to green on successful WebSocket connection
    } else {
        printMsg("WS Failed");
        setLEDState(CRGB::Red); // Set LED to red on WebSocket connection failure
    }
}

void setup() {

    if(ENABLE_LED){
        // Initialize FastLED
        FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(&leds, 1);
        setLEDState(CRGB::White);
    }

    if (DEBUG_SERIAL) Serial.begin(115200);

    if (DEBUG_TFT) {
        // Initialize TFT display
        tft.init();
        tft.setRotation(3); // Adjust rotation as needed
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.fillScreen(TFT_BLACK);
    }

    // Connect to WiFi
    connectToWiFi();

    // Attach WebSocket callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);

    // ########################## NOT NECESSARY FOR NON SSL CONNECTIONS ############################
    client.setCACert(SSL_CERTIFICATE);
    // ########################## NOT NECESSARY FOR NON SSL CONNECTIONS ############################

    // Connect to WebSocket server
    connectToWebSocket();

    // Initialize USB peripherals
    USB.begin();
    delay(50);
    Mouse.begin();
    delay(50);
}

void ensureWiFiConnected() {
    if (WiFi.status() != WL_CONNECTED) {
        printMsg("WiFi Disconnected. Reconnecting...");
        setLEDState(CRGB::Yellow); // Indicate reconnecting with yellow LED
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            printMsg("Attempting WiFi Reconnect...");
            if (millis() - startAttemptTime > 10000) { // Timeout after 10 seconds
                printMsg("WiFi Reconnect Failed");
                return;
            }
        }
        printMsg("WiFi Reconnected");
        setLEDState(CRGB::Green); // Indicate WiFi reconnected
    }
}

void ensureWebSocketConnected() {
    if (!client.available()) {
        printMsg("WebSocket Disconnected.");
        setLEDState(CRGB::Red); // Indicate WebSocket disconnected with red LED

        if (client.connect(WEBSOCKETS_URL)) {
            printMsg("WebSocket Reconnected");
            setLEDState(CRGB::Green); // Indicate WebSocket reconnected
        } else {
            printMsg("WebSocket Failed");
        }
    }
}

void loop() {
    // Check and maintain WiFi connection
    ensureWiFiConnected();

    // Check and maintain WebSocket connection
    ensureWebSocketConnected();

    // Poll WebSocket messages
    client.poll();

    // Call the mouse jiggler logic
    checkJiggle();
}
