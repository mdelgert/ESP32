#include "KeySettings.h"
#include <EEPROM.h>

#define SIZE sizeof(DeviceSettings)

DeviceSettings readSettings() {
  DeviceSettings settings;
  for (int i = 0; i < SIZE; i++) {
    *((char*)&settings + i) = EEPROM.read(i);
  }
  return settings;
}

void checkData() {
  if (!EEPROM.begin(SIZE)) {
    Serial.println("\nFailed to initialise EEPROM!");
    delay(1000000);
  }
}

void printSettings() {
  DeviceSettings settings = readSettings();
  Serial.print("Name: ");
  Serial.println(settings.Name);
  Serial.print("SSID: ");
  Serial.println(settings.SSID);
  Serial.print("Password: ");
  Serial.println(settings.Password);
}

void writeSettings(const DeviceSettings &settings) {
  for (int i = 0; i < SIZE; i++) {
    EEPROM.write(i, *((char*)&settings + i));
  }
  EEPROM.commit();
}

void saveSettings() {
  DeviceSettings settings;
  strcpy(settings.Name, "M5Device2");
  strcpy(settings.SSID, "SSID1");
  strcpy(settings.Password, "pass");
  writeSettings(settings);
}