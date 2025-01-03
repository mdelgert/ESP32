#include "M5Atom.h"
#include <EEPROM.h>

struct DeviceSettings {
  char Name[21];    // Maximum 20 characters + null terminator
  char SSID[21];    // Maximum 20 characters + null terminator
  char Password[41]; // Maximum 40 characters + null terminator
  char Passcode1[41]; // Maximum 40 characters + null terminator
  char Passcode2[41]; // Maximum 40 characters + null terminator
  char Passcode3[41]; // Maximum 40 characters + null terminator
  char Passcode4[41]; // Maximum 40 characters + null terminator
};

#define SIZE sizeof(DeviceSettings)

enum ButtonState { NOT_PRESSED,PRESSED,PRINTED };

ButtonState currentState = NOT_PRESSED;

int addr = 0;

void setup() {
  M5.begin(true, false, true);

  if (!EEPROM.begin(SIZE)) {
    //Serial.println("\nFailed to initialise EEPROM!");
    delay(1000000);
  }

  delay(50);
  M5.dis.drawpix(0, 0xff0000);
  Serial.println("\n"); //Print empty line
  //printSettings(); 
}

DeviceSettings readSettings() {
  DeviceSettings settings;
  for (int i = 0; i < SIZE; i++) {
    *((char*)&settings + i) = EEPROM.read(i);
  }
  return settings;
}

void printSettings()
{
  DeviceSettings settings = readSettings();
  Serial.print("Name: ");
  Serial.println(settings.Name);
  Serial.print("SSID: ");
  Serial.println(settings.SSID);
  Serial.print("Password: ");
  Serial.println(settings.Password);
  Serial.print("Passcode1: ");
  Serial.println(settings.Passcode1);
  Serial.print("Passcode2: ");
  Serial.println(settings.Passcode2);
  Serial.print("Passcode3: ");
  Serial.println(settings.Passcode3);
  Serial.print("Passcode4: ");
  Serial.println(settings.Passcode4);
}

void writeSettings(const DeviceSettings &settings) {
  for (int i = 0; i < SIZE; i++) {
    EEPROM.write(i, *((char*)&settings + i));
  }
  EEPROM.commit();
}

void saveSettings()
{
  DeviceSettings settings;
  strcpy(settings.Name, "M5Device2");
  strcpy(settings.SSID, "SSID1");
  strcpy(settings.Password, "pass");
  strcpy(settings.Passcode1, "pass1");
  strcpy(settings.Passcode2, "pass2");
  strcpy(settings.Passcode3, "pass3");
  strcpy(settings.Passcode4, "pass4");
  writeSettings(settings);
}

void loop() {
  if (M5.Btn.isPressed()) {
    M5.dis.drawpix(0, 0x0000f0);
    if (currentState == NOT_PRESSED) {
      currentState = PRESSED;
      saveSettings();
      printSettings();
    }
  } else {
    if (currentState == PRESSED) {
      currentState = PRINTED;
    } else if (currentState == PRINTED) {
      currentState = NOT_PRESSED;
      M5.dis.drawpix(0, 0xff0000);
    }
  }

  delay(50);
  M5.update();
}