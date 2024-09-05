#include <WiFi.h>
#include "WiFiHandler.h"
#include "DisplayHandler.h"
#include "SettingsHandler.h"  // Include SettingsHandler to get the settings

void initializeWiFi()
{
    // Get settings from SettingsHandler
    DeviceSettings settings = getParsedSettings();

    // Set the device name as the network hostname
    WiFi.setHostname(settings.device_name.c_str());

    // Use the SSID and password from the settings
    WiFi.begin(settings.wifi_ssid.c_str(), settings.wifi_password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        displayMessage("Connecting...");
    }

    // Display the IP address when connected
    String ipAddress = WiFi.localIP().toString();
    displayMessage(ipAddress.c_str());
}
