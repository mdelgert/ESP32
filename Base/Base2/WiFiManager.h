#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include "Config.h"
#include "LogManager.h"

class WiFiManager {
public:
    void init() {
        if (!ENABLE_WIFI) return;

        LogManager::log("Connecting to Wi-Fi...");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            LogManager::log(".");
        }

        LogManager::log("Wi-Fi connected. IP: " + WiFi.localIP().toString());
    }
};

#endif // WIFI_MANAGER_H
