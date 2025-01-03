#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <TFT_eSPI.h> // Include the TFT display library
#include "USB.h"
#include "USBHIDKeyboard.h" // Include the USB HID Keyboard library
#include "ConfigSecure.h" // Include configuration file

using namespace websockets;

// TFT display instance
TFT_eSPI tft = TFT_eSPI();

// WebSocket client instance
WebsocketsClient client;

// USB HID Keyboard instance
USBHIDKeyboard Keyboard;

// Message counter for TFT
int messageCounter = 0;

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

// Function to send messages to USB HID Keyboard in chunks
void sendToKeyboard(String message) {
    for (int i = 0; i < message.length(); i += CHUNK_SIZE) {
        String chunk = message.substring(i, i + CHUNK_SIZE);
        for (int j = 0; j < chunk.length(); j++) {
            Keyboard.print(chunk[j]);
            delay(CHAR_DELAY); // Delay between characters
        }
        delay(CHUNK_DELAY); // Delay between chunks
    }
    Keyboard.println(); // Add a newline at the end
}

// Callback for incoming WebSocket messages
void onMessageCallback(WebsocketsMessage message) {
    String receivedMessage = message.data();
    printMsg(receivedMessage.c_str()); // Display message on TFT and/or Serial
    //messageCounter++; // Increment the counter for each message
    //printMsg("Msg%d", messageCounter); // Print counter to TFT
    //sendToKeyboard(receivedMessage);  // Send message to USB HID Keyboard
}

// Callback for WebSocket events
void onEventsCallback(WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
        printMsg("WS Connected");
    } else if (event == WebsocketsEvent::ConnectionClosed) {
        printMsg("WS Disconnected");
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
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printMsg("Connecting..."); // Display connecting status repeatedly
    }
    printMsg("WiFi Connected");
}

// Function to connect to WebSocket
void connectToWebSocket() {
    printMsg("Connecting to WS...");
    if (client.connect(WEBSOCKETS_URL)) {
        printMsg("WS Connected");
    } else {
        printMsg("WS Failed");
    }
}

void setup() {
    if (DEBUG_SERIAL) Serial.begin(115200);

    if (DEBUG_TFT) {
        // Initialize TFT display
        tft.init();
        tft.setRotation(3); // Adjust rotation as needed
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.fillScreen(TFT_BLACK);
    }

    // Initialize USB HID Keyboard
    USB.begin();
    Keyboard.begin();

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
