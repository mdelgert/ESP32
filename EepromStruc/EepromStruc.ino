#include <EEPROM.h>
#include "M5Atom.h"

enum ButtonState { NOT_PRESSED, PRESSED, PRINTED };

ButtonState currentState = NOT_PRESSED;

// Define your structure
struct DeviceSettings {
  String Name;
  String SSID;
  String Password;
};

void writeSettingsToDevice() {
  DeviceSettings mySettings;
  mySettings.Name = "MyDevice";
  mySettings.SSID = "MyNetwork";
  mySettings.Password = "MyPassword";
  EEPROM.put(0, mySettings);
}

void readSettingsFromDevice() {
  DeviceSettings readSettings;
  EEPROM.get(0, readSettings);
  Serial.println("Read settings:");
  Serial.print("Name: ");
  Serial.println(readSettings.Name);
  Serial.print("SSID: ");
  Serial.println(readSettings.SSID);
  Serial.print("Password: ");
  Serial.println(readSettings.Password);
}

void setup() {
  Serial.begin(115200);
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, 0xff0000);
  writeSettingsToDevice();
}

void loop() {
    if (M5.Btn.isPressed()) {
        M5.dis.drawpix(0, 0x0000f0);
        if (currentState == NOT_PRESSED) {
            currentState = PRESSED;    
            Serial.println("Keypressed!");
            // Read settings from EEPROM
            readSettingsFromDevice();
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
