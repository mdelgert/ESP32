/*
 * This code sets up a WebSocket client using the ArduinoWebsockets library and displays incoming messages on a TFT screen using the TFT_eSPI library.
 * It includes:
 * - Initialization of the TFT display.
 * - Initialization of the WebSocket client.
 * - Timer functionality to send messages at regular intervals.
 * - A function to print messages to the TFT screen.
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

// Timer variables
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Send message every 1 second

// Counter for messages
int messageCount = 0;

// Function to print messages to TFT
void printToTFT(const char* message) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.println(message);
    Serial.println(message);
}

// Callback for incoming WebSocket messages
void onMessageCallback(WebsocketsMessage message) {
    Serial.println("Got Message:");
    Serial.println(message.data());
    printToTFT(message.data().c_str());
}

// Callback for WebSocket events
void onEventsCallback(WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connection Opened");
        printToTFT("WS Connected");
    } else if (event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connection Closed");
        printToTFT("WS Closed");
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
    tft.setRotation(3);
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
    client.poll();

    // Timer-based message sending
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        
        // Increment and send message
        messageCount++;
        String message = "Hello " + String(messageCount);
        if (client.available()) {
            client.send(message);
            Serial.println("Sent: " + message);
            printToTFT(message.c_str());
        } else {
            Serial.println("WebSocket Not Available");
        }
    }
}
