//SettingsHandler.h

#ifndef SETTINGS_HANDLER_H
#define SETTINGS_HANDLER_H

#include <Arduino.h>

// Struct for device and Wi-Fi settings
struct DeviceSettings {
    String device_name;
    bool setup_mode;
    String admin;
    String device_password;
    String wifi_ssid;
    String wifi_password;
};

// Function declarations
void saveSettings(const String &json);
String getSettings();
DeviceSettings getParsedSettings();

#endif  // SETTINGS_HANDLER_H
