#ifndef WEBSOCKET_CLIENT_HANDLER_H
#define WEBSOCKET_CLIENT_HANDLER_H

#include <ArduinoWebsockets.h>
#include "Config.h"
#include "Cert.h"
#include "LogManager.h"
#include "LEDHandler.h"
#include "KeyboardMouseHandler.h"

using namespace websockets;

class WebSocketClientHandler {
private:
    static WebsocketsClient client;
    static bool initialized;
    static unsigned long lastReconnectAttempt;
    static unsigned long reconnectDelay;
    static const unsigned long maxReconnectDelay;

public:
    // Initialize WebSocket client
    static void init() {
        if (!ENABLE_WEBSOCKET) {
            LogManager::log("WebSocket is disabled (ENABLE_WEBSOCKET is false).");
            LEDHandler::setColor(CRGB::Yellow); // Indicate disabled WebSocket
            return;
        }

        LogManager::log("Connecting to WebSocket: " + String(WEBSOCKET_URL));
        reconnectDelay = 1000; // Reset initial reconnect delay

        connect();
    }

    // Attempt to connect to the WebSocket server
    static void connect() {
        // Use SSL Certificate if ENABLE_SSL is true
        if (ENABLE_SSL) {
            client.setCACert(SSL_CERTIFICATE);
            LogManager::log("SSL enabled with certificate.");
        } else {
            client.setInsecure(); // Allow insecure connection
            LogManager::log("SSL disabled.");
        }

        if (!client.connect(WEBSOCKET_URL)) {
            LogManager::log("Failed to connect to WebSocket server.");
            LEDHandler::setColor(CRGB::Yellow); // Indicate connection failure
            return;
        }

        client.onMessage(onMessageCallback);
        client.onEvent(onEventCallback);

        initialized = true;
        LogManager::log("Connected to WebSocket server.");
        LEDHandler::setColor(CRGB::Blue); // Indicate successful connection
    }

    // Recovery logic for disconnection
    static void recover() {
        unsigned long currentMillis = millis();
        if (currentMillis - lastReconnectAttempt >= reconnectDelay) {
            lastReconnectAttempt = currentMillis;

            LogManager::log("Attempting to reconnect to WebSocket...");
            connect();

            // Exponential backoff
            if (!initialized) {
                reconnectDelay = min(reconnectDelay * 2, maxReconnectDelay);
                LogManager::log("Reconnect failed. Next attempt in " + String(reconnectDelay / 1000) + " seconds.");
            } else {
                reconnectDelay = 1000; // Reset delay on successful connection
            }
        }
    }

    // Send a message to the WebSocket server
    static void sendMessage(const String &message) {
        if (!ENABLE_WEBSOCKET) {
            LogManager::log("WebSocket is disabled.");
            return;
        }

        if (!initialized) {
            LogManager::log("WebSocketClientHandler not initialized.");
            return;
        }

        LogManager::log("Sending WebSocket message: " + message);
        client.send(message);
    }

    // Handle incoming messages
    static void onMessageCallback(WebsocketsMessage message) {
        String msg = message.data();
        //LogManager::log("Received WebSocket message: " + msg);
        LogManager::log(msg);

        // Send keys using KeyboardMouseHandler
        if (ENABLE_USB_HID) {
            KeyboardMouseHandler::sendKeys(msg.c_str());
        } 
        // else {
        //     LogManager::log("USB HID is disabled. Skipping key input.");
        // }
    }

    // Handle WebSocket events
    static void onEventCallback(WebsocketsEvent event, String data) {
        switch (event) {
        case WebsocketsEvent::ConnectionOpened:
            LogManager::log("WebSocket connection opened.");
            LEDHandler::setColor(CRGB::Blue); // Indicate successful connection
            initialized = true;
            break;
        case WebsocketsEvent::ConnectionClosed:
            LogManager::log("WebSocket connection closed.");
            LEDHandler::setColor(CRGB::Yellow); // Indicate disconnection
            initialized = false;
            break;
        default:
            //LogManager::log("Unknown WebSocket event.");
            break;
        }
    }

    // Process WebSocket client (call in loop)
    static void loop() {
        if (!ENABLE_WEBSOCKET) return;

        if (!client.available()) {
            recover(); // Trigger recovery logic if disconnected
        } else {
            client.poll(); // Process incoming WebSocket events
        }
    }
};

// Static member definitions
WebsocketsClient WebSocketClientHandler::client;
bool WebSocketClientHandler::initialized = false;
unsigned long WebSocketClientHandler::lastReconnectAttempt = 0;
unsigned long WebSocketClientHandler::reconnectDelay = 1000;
const unsigned long WebSocketClientHandler::maxReconnectDelay = 30000; // 30 seconds

#endif // WEBSOCKET_CLIENT_HANDLER_H
