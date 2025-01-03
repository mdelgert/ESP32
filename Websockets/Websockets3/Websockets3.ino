#define FASTLED_INTERNAL //remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#include <FastLED.h>
#include <ArduinoJson.h> // Ensure ArduinoJson library is included
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include "ConfigSecure.h"
#include "ConfigPins.h"

using namespace websockets;

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
bool JigglerEnabled;  // Defaults to false

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

    // Set the SSL certificate
    client.setCACert(SSL_CERTIFICATE);

    // Connect to WebSocket server
    connectToWebSocket();
}

void loop() {
    client.poll(); // Keep WebSocket connection alive and process incoming messages
}
