#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include "Config.h"
#include "LogManager.h"
#include "LEDHandler.h"

class WiFiHandler {
private:
    static bool initialized;
    static unsigned long lastReconnectAttempt;
    static unsigned long reconnectDelay;
    static const unsigned long maxReconnectDelay;

    // Log the current Wi-Fi status
    static void logStatus() {
        if (WiFi.status() == WL_CONNECTED) {
            LogManager::log("Wi-Fi connected: " + WiFi.localIP().toString());
            LEDHandler::setColor(CRGB::Green); // Indicate successful connection
        } else {
            LogManager::log("Wi-Fi not connected.");
            LEDHandler::setColor(CRGB::Red); // Indicate disconnection
        }
    }

    // Attempt to reconnect to Wi-Fi
    static void reconnect() {
        LogManager::log("Reconnecting to Wi-Fi...");
        WiFi.reconnect();

        unsigned long currentMillis = millis();
        if (currentMillis - lastReconnectAttempt >= reconnectDelay) {
            lastReconnectAttempt = currentMillis;

            int retries = 10; // Retry limit for immediate attempts
            while (WiFi.status() != WL_CONNECTED && retries > 0) {
                delay(500);
                retries--;
            }

            // Log status and update LED
            logStatus();

            // Exponential backoff for next attempt
            if (WiFi.status() != WL_CONNECTED) {
                reconnectDelay = min(reconnectDelay * 2, maxReconnectDelay);
                LogManager::log("Reconnect failed. Next attempt in " + String(reconnectDelay / 1000) + " seconds.");
            } else {
                reconnectDelay = 1000; // Reset delay on successful connection
            }
        }
    }

public:
    // Initialize Wi-Fi with predefined credentials
    static void init() {
        if (!ENABLE_WIFI) {
            LogManager::log("Wi-Fi is disabled (ENABLE_WIFI is false).");
            LEDHandler::setColor(CRGB::Red); // Indicate disabled Wi-Fi
            return;
        }

        if (initialized) {
            LogManager::log("WiFiHandler already initialized.");
            return;
        }

        LogManager::log("Initializing Wi-Fi...");
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        int retries = 20; // Retry limit (10 seconds)
        while (WiFi.status() != WL_CONNECTED && retries > 0) {
            delay(500);
            LogManager::log("Connecting to Wi-Fi...");
            retries--;
        }

        logStatus(); // Log status and update LED
        initialized = true;
    }

    // Maintain Wi-Fi connection (call in loop)
    static void maintain() {
        if (!ENABLE_WIFI) return;

        if (WiFi.status() != WL_CONNECTED) {
            reconnect(); // Trigger recovery logic
        }
    }

    // Disconnect Wi-Fi
    static void disconnect() {
        if (!ENABLE_WIFI) return;

        if (WiFi.status() == WL_CONNECTED) {
            WiFi.disconnect();
            LogManager::log("Wi-Fi disconnected.");
            LEDHandler::setColor(CRGB::Red); // Indicate disconnection
        }
    }

    // Get Wi-Fi connection status
    static bool isConnected() {
        if (!ENABLE_WIFI) return false;
        return WiFi.status() == WL_CONNECTED;
    }

    // Get the IP address
    static String getIPAddress() {
        if (!ENABLE_WIFI) return "Wi-Fi disabled";
        return WiFi.localIP().toString();
    }
};

// Static member definitions
bool WiFiHandler::initialized = false;
unsigned long WiFiHandler::lastReconnectAttempt = 0;
unsigned long WiFiHandler::reconnectDelay = 1000;
const unsigned long WiFiHandler::maxReconnectDelay = 30000; // 30 seconds

#endif // WIFI_HANDLER_H
