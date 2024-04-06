#ifndef KEYSETTINGS_H
#define KEYSETTINGS_H

struct DeviceSettings {
  char Name[21];    // Maximum 20 characters + null terminator
  char SSID[21];    // Maximum 20 characters + null terminator
  char Password[41]; // Maximum 40 characters + null terminator
};

DeviceSettings readSettings();
void checkData();
void printSettings();
void writeSettings(const DeviceSettings &settings);
void saveSettings();

#endif
