#include <Preferences.h>
#include <ArduinoJson.h>
#include "SettingsHandler.h"
#include "ConfigSecure.h"  // Include the fallback values

Preferences preferences;
const char* SETTINGS_NAMESPACE = "device_settings";
const char* SETTINGS_KEY = "settings";

DeviceSettings getParsedSettings() {
    DeviceSettings settings;

    preferences.begin(SETTINGS_NAMESPACE, true);  // Open preferences in read-only mode
    String json = preferences.getString(SETTINGS_KEY, "{}");  // Get the saved JSON
    preferences.end();

    // Parse JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, json);

    if (error || doc.isNull()) {
        // Fallback to default values from ConfigSecure.h
        settings.device_name = DEVICE_NAME;
        settings.setup_mode = DEVICE_SETUP;
        settings.admin = DEVICE_ADMIN;
        settings.device_password = DEVICE_PASSWORD;
        settings.wifi_ssid = SSID;
        settings.wifi_password = PASSWORD;
    } else {
        // Extract device settings, falling back to ConfigSecure.h if any are missing
        settings.device_name = doc["device"]["name"] | DEVICE_NAME;
        settings.setup_mode = doc["device"]["setup_mode"] | DEVICE_SETUP;
        settings.admin = doc["device"]["admin"] | DEVICE_ADMIN;
        settings.device_password = doc["device"]["password"] | DEVICE_PASSWORD;

        // Extract Wi-Fi settings, falling back to ConfigSecure.h if any are missing
        settings.wifi_ssid = doc["wifi"]["ssid"] | SSID;
        settings.wifi_password = doc["wifi"]["password"] | PASSWORD;
    }

    return settings;
}
