#include "M5Atom.h"
#include <EEPROM.h>

enum ButtonState { NOT_PRESSED,PRESSED,PRINTED };

ButtonState currentState = NOT_PRESSED;

int addr = 0;    // EEPROM Start number of an ADDRESS.
#define SIZE 32  // Define the size of EEPROM(Byte).

void setup() {
  M5.begin(true, false, true);

  if (!EEPROM.begin(SIZE)) {                           // Request storage of SIZE size(success return1). output format string
    Serial.println("\nFailed to initialise EEPROM!");
    delay(1000000);
  }

  Serial.println("\nRead data from EEPROM. Values are:");
  for (int i = 0; i < SIZE; i++) {
    Serial.printf("%d ", EEPROM.read(i));  // Reads data from 0 to SIZE in EEPROM.
  }

  delay(50);
  M5.dis.drawpix(0, 0xff0000);
}

void writeData(const char* data) {
  Serial.printf("\n%d Bytes data written on EEPROM.\nValues are:\n", strlen(data) + 1); // +1 for null terminator
  int len = strlen(data);
  for (int i = 0; i < len; i++) {
    EEPROM.write(addr, data[i]);  // Writes the specified data to the specified address.
    Serial.print(data[i]);
    addr += 1;  // Go to the next storage address.
  }
  EEPROM.write(addr, '\0'); // Null terminator
  Serial.println("\0");
  addr += 1; // Move to the next address after null terminator
  addr = 0; // When the storage address sequence number reaches the end of the storage space of the EEPROM, return to.
}

void readData() {
  Serial.println("\nRead from EEPROM. Values are:");
  for (int i = 0; i < SIZE; i++) {
    char value = (char)EEPROM.read(i);
    if (value == '\0') // Stop printing when null character is encountered
      break;
    Serial.print(value);
  }
  //Serial.println("\n-------------------------------------\n");
}


void loop() {
  if (M5.Btn.isPressed()) {
    M5.dis.drawpix(0, 0x0000f0);
    if (currentState == NOT_PRESSED) {
      currentState = PRESSED;
      const char* data = "~!@#$%^&*()1234567890";
      writeData(data);
      readData();
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