#include <Preferences.h>
#include <ArduinoJson.h>
#include "SettingsHandler.h"
#include "ConfigSecure.h" // Include the fallback values
#include "DisplayHandler.h" // Include the display handler

Preferences preferences;
const char *SETTINGS_NAMESPACE = "device_settings";
const char *SETTINGS_KEY = "settings";

// Function to load fallback/default values from ConfigSecure.h
void loadFallbackSettings(DeviceSettings &settings)
{
    settings.device_name = DEVICE_NAME;
    settings.setup_mode = DEVICE_SETUP;
    settings.admin = DEVICE_ADMIN;
    settings.device_password = DEVICE_PASSWORD;
    settings.wifi_ssid = SSID;
    settings.wifi_password = PASSWORD;
}

DeviceSettings getParsedSettings()
{
    DeviceSettings settings;

    preferences.begin(SETTINGS_NAMESPACE, true);           // Open preferences in read-only mode
    String json = preferences.getString(SETTINGS_KEY, ""); // Get the saved JSON, return empty if not found
    preferences.end();

    // Parse JSON and handle both empty JSON and parsing errors in a single check
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, json);

    if (error) 
    {
        displayMessage("JSON ERROR");
        delay(3000);

        // Handle JSON error case by loading fallback values
        loadFallbackSettings(settings);
    } 
    else 
    {
        // No error in JSON parsing, extract device settings
        settings.device_name = doc["device"]["name"] | DEVICE_NAME;
        settings.setup_mode = doc["device"]["setup_mode"].as<bool>(); // Explicitly cast to bool
        settings.admin = doc["device"]["admin"] | DEVICE_ADMIN;
        settings.device_password = doc["device"]["password"] | DEVICE_PASSWORD;

        // Extract Wi-Fi settings
        settings.wifi_ssid = doc["wifi"]["ssid"] | SSID;
        settings.wifi_password = doc["wifi"]["password"] | PASSWORD;

        // If DEVICE_FALLBACK is set, override with fallback values
        if (DEVICE_FALLBACK)
        {
            displayMessage("Fallback");
            delay(1000);
            loadFallbackSettings(settings);
        }

        // Display extracted values with short messages
        displayMessage(("Device:" + settings.device_name).c_str());
        displayMessage(("Mode:" + String(settings.setup_mode)).c_str());
        displayMessage(("WiFi:" + settings.wifi_ssid).c_str());
    }

    return settings;
}

// Save JSON settings to preferences
void saveSettings(const String &json)
{
    preferences.begin(SETTINGS_NAMESPACE, false);
    preferences.putString(SETTINGS_KEY, json);
    preferences.end();
}

// Retrieve the saved JSON settings
String getSettings()
{
    preferences.begin(SETTINGS_NAMESPACE, true);
    String json = preferences.getString(SETTINGS_KEY, "{}");
    preferences.end();
    return json;
}
