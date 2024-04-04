//https://github.com/m5stack/M5Atom/blob/master/examples/Advanced/Storage/EEPROM/EEPROM.ino

#include <M5Atom.h>
#include <EEPROM.h>

struct DeviceSettings {
  String Name;
  String SSID;
  String Password;
};

int addr = 0;                        // EEPROM Start number of an ADDRESS.
#define SIZE sizeof(DeviceSettings)  // define the size of EEPROM(Byte).

void setup() {
  M5.begin();                 // Init Atom.
  if (!EEPROM.begin(SIZE)) {  // Request storage of SIZE size.
    Serial.println("\nFailed to initialise EEPROM!");
    delay(1000000);
  }
  Serial.println("\nRead data from EEPROM. Values are:");
  for (int i = 0; i < SIZE; i++) {
    Serial.printf("%c", EEPROM.read(i));  // Read data from 0 to SIZE in EEPROM.
  }
  Serial.println("\n\nPress Btn to Write EEPROM");
}

void writeSettingsToDevice() {

  DeviceSettings settings;
  
  settings.Name = "MyDevice1";
  settings.SSID = "MyNetwork2";
  settings.Password = "password~!@#$%^&*()1234567890";

  for (int i = 0; i < SIZE; i++) {
    if (i < sizeof(settings)) {
      EEPROM.write(addr + i, *((char*)&settings + i));
    } else {
      EEPROM.write(addr + i, 0);  // Clear any remaining bytes in EEPROM
    }
  }
}

DeviceSettings readSettingsFromDevice() {
  
  DeviceSettings settings;

  for (int i = 0; i < SIZE; i++) {
    *((char*)&settings + i) = EEPROM.read(addr + i);
  }

  Serial.println("\nRead settings:");
  Serial.print("Name: ");
  Serial.println(settings.Name);
  Serial.print("SSID: ");
  Serial.println(settings.SSID);
  Serial.print("Password: ");
  Serial.println(settings.Password);
}

void loop() {
  M5.update();               // Check button down state.
  if (M5.Btn.isPressed()) {  // if the button is Pressed.
    Serial.println("\n\nWrite data to EEPROM");

    // Write settings to EEPROM
    writeSettingsToDevice();

    // Read settings from EEPROM
    readSettingsFromDevice();

      Serial.println("\n-------------------------------------\n");
  }
  delay(150);
}
