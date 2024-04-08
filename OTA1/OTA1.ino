#include <M5Atom.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <EEPROM.h>
#define SIZE sizeof(DeviceSettings)

struct DeviceSettings {
  char HostName[21];
  char SSID[21];
  char PasswordSSID[41];
  char PasswordOTA[41];
};

DeviceSettings settings;

void setup() {
  M5.begin(true, false, true);
  delay(50);

  if (!EEPROM.begin(SIZE)) {
    Serial.println("\nFailed to initialise EEPROM!");
    M5.dis.drawpix(0, 0xff0000);  // RED
    delay(1000000);
  }

  readEEPROM();

  //M5.dis.drawpix(0, 0xfff000);  // YELLOW
  //M5.dis.drawpix(0, 0xff0000);  // RED
  //M5.dis.drawpix(0, 0x0000f0);  // BLUE
  //M5.dis.drawpix(0, 0x00ff00);  // GREEN
  M5.dis.drawpix(0, 0xffffff);  // WHITE

  WiFi.begin(settings.SSID, settings.PasswordSSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.dis.drawpix(0, 0xfff000);  // YELLOW
    Serial.print(".");
  }

  printWifi();
  //ArduinoOTA.setHostname(settings.HostName);
  //ArduinoOTA.setPassword(settings.PasswordOTA);
  ArduinoOTA.setHostname("ATOM1");
  ArduinoOTA.setPassword("666666");
  ArduinoOTA.begin();
  Serial.println("OTA ready!");
  M5.dis.drawpix(0, 0x00ff00);  // GREEN
}

void loop() {
  ArduinoOTA.handle();
  M5.update();
  configurationMenu();
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
        printWifi();
        break;
    }
  }
}

void helpMenu() {
  Serial.println("\nHelp:");
  Serial.println("p - Print current settings");
  Serial.println("s - Set device settings");
  Serial.println("h - Display this help menu");
  Serial.println("w - Print wifi settings");
}

void setDeviceSettingsMenu() {

  Serial.println("Enter HostName:");
  readSerial(settings.HostName, sizeof(settings.HostName));
  Serial.println("Enter SSID:");
  readSerial(settings.SSID, sizeof(settings.SSID));
  Serial.println("Enter SSID password:");
  readSerial(settings.PasswordSSID, sizeof(settings.PasswordSSID));
  Serial.println("Enter OTA password:");
  readSerial(settings.PasswordOTA, sizeof(settings.PasswordOTA));
  writeEEPROM(settings);
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

void printWifi() {
  Serial.print("WiFi Connect To: ");
  Serial.println(WiFi.SSID());  // Output Network name.  输出网络名称
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Output IP Address.  输出IP地址
}

void printSettings() {
  readEEPROM();
  Serial.print("HostName: ");
  Serial.println(settings.HostName);
  Serial.print("SSID: ");
  Serial.println(settings.SSID);
  Serial.print("PasswordSSID: ");
  Serial.println(settings.PasswordSSID);
  Serial.print("PasswordOTA: ");
  Serial.println(settings.PasswordOTA);
}

void readEEPROM() {
  for (int i = 0; i < SIZE; i++) {
    *((char*)&settings + i) = EEPROM.read(i);
  }
}

void writeEEPROM(const DeviceSettings& settings) {
  for (int i = 0; i < SIZE; i++) {
    EEPROM.write(i, *((char*)&settings + i));
  }
  EEPROM.commit();
}