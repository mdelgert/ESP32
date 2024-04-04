#include <M5Atom.h>
#include <EEPROM.h>

struct DeviceSettings {
  String Name;
  String SSID;
  String Password;
};

int addr = 0;  // EEPROM Start number of an ADDRESS.
//#define SIZE sizeof(DeviceSettings)  // define the size of EEPROM(Byte).
#define SIZE 180

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

void writeSettingsToDevice(const DeviceSettings &settings) {
    for (int i = 0; i < SIZE; i++) {
        if (i < sizeof(settings)) {
            EEPROM.write(addr + i, *((char*)&settings + i));
        } else {
            EEPROM.write(addr + i, 0); // Clear any remaining bytes in EEPROM
        }
    }
}

DeviceSettings readSettingsFromDevice() {
    DeviceSettings settings;
    for (int i = 0; i < SIZE; i++) {
        *((char*)&settings + i) = EEPROM.read(addr + i);
    }
    return settings;
}

void loop() {
    M5.update();  // Check button down state.
    if (M5.Btn.isPressed()) {  // if the button is Pressed.
        Serial.println("\n\nWrite data to EEPROM");
        // Initialize DeviceSettings struct
        DeviceSettings mySettings;
        mySettings.Name = "d1";
        mySettings.SSID = "wap1";
        mySettings.Password = "password~!@#$%^&*()1234567890";

        // Write settings to EEPROM
        writeSettingsToDevice(mySettings);

        // Read settings from EEPROM
        DeviceSettings readSettings = readSettingsFromDevice();

        // Print out the read data
        Serial.println("\nRead settings:");
        Serial.print("Name: ");
        Serial.println(readSettings.Name);
        Serial.print("SSID: ");
        Serial.println(readSettings.SSID);
        Serial.print("Password: ");
        Serial.println(readSettings.Password);

        Serial.println("\n-------------------------------------\n");
    }
    delay(150);
}
