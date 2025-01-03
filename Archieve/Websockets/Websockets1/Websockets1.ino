/*
 * This code sets up a WebSocket client using the ArduinoWebsockets library and displays incoming messages on a TFT screen using the TFT_eSPI library.
 * It includes:
 * - Initialization of the TFT display.
 * - Initialization of the WebSocket client.
 * - A function to print messages to the TFT screen.
 * - A callback function to handle incoming WebSocket messages and display them on the TFT screen.
 */
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <TFT_eSPI.h> // Include the TFT display library
#include "ConfigSecure.h" // Include configuration file

using namespace websockets;

// TFT display instance
TFT_eSPI tft = TFT_eSPI();

// WebSocket client instance
WebsocketsClient client;

// Function to print messages to TFT
void printToTFT(const char* message) {
    tft.fillScreen(TFT_BLACK); // Clear the screen
    tft.setCursor(10, 10);     // Set cursor position
    tft.println(message);      // Print message to TFT
    Serial.println(message);   // Debug log to Serial Monitor
}

// Callback for incoming WebSocket messages
void onMessageCallback(WebsocketsMessage message) {
    Serial.println("Got Message:");
    Serial.println(message.data());
    printToTFT(message.data().c_str()); // Print message content to TFT
}

// Callback for WebSocket events
void onEventsCallback(WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("WebSocket Connected");
        printToTFT("WS Connected");
    } else if (event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("WebSocket Disconnected");
        printToTFT("WS Disconnected");
    } else if (event == WebsocketsEvent::GotPing) {
        Serial.println("Ping Received");
    } else if (event == WebsocketsEvent::GotPong) {
        Serial.println("Pong Received");
    }
}

void setup() {
    Serial.begin(115200);

    // Initialize TFT display
    tft.init();
    tft.setRotation(3); // Adjust rotation as needed
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.fillScreen(TFT_BLACK);
    printToTFT("Connecting...");

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    printToTFT("WiFi Connected");
    Serial.println("\nWiFi Connected");

    // Attach WebSocket callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);

    // Set the SSL certificate
    client.setCACert(SSL_CERTIFICATE);

    // Connect to WebSocket server
    printToTFT("Connecting to WS...");
    if (client.connect(WEBSOCKETS_URL)) {
        Serial.println("WebSocket Connected");
        printToTFT("WS Connected");
    } else {
        Serial.println("WebSocket Connection Failed");
        printToTFT("WS Failed");
    }
}

void loop() {
    client.poll(); // Keep WebSocket connection alive and process incoming messages
}
