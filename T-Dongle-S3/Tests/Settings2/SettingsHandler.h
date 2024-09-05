#ifndef SETTINGS_HANDLER_H
#define SETTINGS_HANDLER_H

#include <Arduino.h>

struct DeviceSettings {
    // Device settings
    String device_name;
    bool setup_mode;
    String admin;
    String device_password;

    // Wi-Fi settings
    String wifi_ssid;
    String wifi_password;
};

// Function to retrieve parsed settings as a struct, with fallback to ConfigSecure.h
DeviceSettings getParsedSettings();

#endif // SETTINGS_HANDLER_H
