#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <Preferences.h>
#include "MessagePrinter.h"

class WiFiManager {
private:
    MessagePrinter &printer;
    Preferences preferences;
    String ssid;
    String password;

    void loadPreferences() {
        if (preferences.begin("config", true)) {  // Read-only mode
            ssid = preferences.getString("wifi_ssid", DEFAULT_WIFI_SSID);
            password = preferences.getString("wifi_password", DEFAULT_WIFI_PASSWORD);
            preferences.end();
        }
    }

public:
    WiFiManager(MessagePrinter &printer)
        : printer(printer), ssid(DEFAULT_WIFI_SSID), password(DEFAULT_WIFI_PASSWORD) {}

    void init() {
        preferences.begin("config", false);
        loadPreferences();
        connectToWiFi();
    }

    void connectToWiFi() {
        WiFi.begin(ssid.c_str(), password.c_str());
        int attempts = 0;

        while (WiFi.status() != WL_CONNECTED && attempts < 10) {
            printer.print("Connecting to WiFi...");
            delay(500);
            attempts++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            printer.print("WiFi Connected: " + WiFi.localIP().toString());
        } else {
            printer.print("WiFi Connection Failed!");
        }
    }

    void saveWiFiSettings(const String &newSsid, const String &newPassword) {
        preferences.putString("wifi_ssid", newSsid);
        preferences.putString("wifi_password", newPassword);
        printer.print("Wi-Fi settings saved.");
    }
};

#endif
