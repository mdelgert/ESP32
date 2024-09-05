//WiFiHandler.cpp

#include <WiFi.h>
#include "WiFiHandler.h"
#include "DisplayHandler.h"
#include "SettingsHandler.h"  // Include SettingsHandler to get the settings

void initializeWiFi()
{
    // Get settings from SettingsHandler
    DeviceSettings settings = getParsedSettings();

    if (settings.setup_mode) {
        // displayMessage("Setup");
        // delay(3000);

        // displayMessage(settings.device_password.c_str());
        // delay(3000);

        // If setup mode is true, set up the device as a wireless access point
        WiFi.softAP(settings.device_name.c_str(), settings.device_password.c_str());

        String ipAddress = WiFi.softAPIP().toString();  // Get the IP address of the access point
        displayMessage(ipAddress.c_str());  // Display IP only
    } else {
        // Set the device name as the network hostname
        WiFi.setHostname(settings.device_name.c_str());

        // Use the SSID and password from the settings to connect to Wi-Fi
        WiFi.begin(settings.wifi_ssid.c_str(), settings.wifi_password.c_str());

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        }

        // Display the IP address when connected
        String ipAddress = WiFi.localIP().toString();
        displayMessage(ipAddress.c_str());  // Display IP only
    }
}
