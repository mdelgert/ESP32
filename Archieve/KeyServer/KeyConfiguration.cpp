#include "KeyConfiguration.h"
#include "KeySettings.h"
#include "KeyWeb.h"

void helpMenu() {
  Serial.println("\nHelp:");
  Serial.println("p - Print current settings");
  Serial.println("s - Set device settings");
  Serial.println("h - Display this help menu");
  Serial.println("w - Display webserver info");
}

void configurationMenu() {
  if (Serial.available() > 0) {
    char option = Serial.read();  // Read user's option
    switch (option) {
      case 'p':
        printSettings();
        break;
      case 's':
        setDeviceSettingsMenu();
        break;
      case 'h':
        helpMenu();
        break;
      case 'w':
        keyWebPrint();
        break;
    }
  }
}

void setDeviceSettingsMenu() {
  DeviceSettings settings;
  Serial.println("Enter name:");
  readSerial(settings.Name, sizeof(settings.Name));
  Serial.println("Enter ssid:");
  readSerial(settings.SSID, sizeof(settings.SSID));
  Serial.println("Enter password:");
  readSerial(settings.Password, sizeof(settings.Password));
  writeSettings(settings);
  printSettings();
}

void readSerial(char* data, int maxLength) {
  while (true) {
    if (Serial.available() > 0) {
      int i = 0;
      while (Serial.available() > 0 && i < maxLength) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
          data[i] = '\0';  // Null terminate the string
          return;
        } else {
          data[i] = c;
          i++;
        }
      }
      data[i] = '\0';  // Null terminate the string
      return;
    }
  }
}