#include "PreferencesHandler.h"

class WiFiHandler {
public:
    static void init() {
        String ssid;
        String password;
        PreferencesHandler::getInstance().getValue("WifiSSID", ssid);
        PreferencesHandler::getInstance().getValue("WifiPassword", password);

        if (!ssid.isEmpty() && !password.isEmpty()) {
            Serial.printf("Connecting to WiFi: %s\n", ssid.c_str());
            // Add WiFi connection logic here...
        } else {
            Serial.println("WiFi settings not found.");
        }
    }
};
