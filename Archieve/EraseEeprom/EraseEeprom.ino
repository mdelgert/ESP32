/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * Please see eeprom_iteration for a more in depth
 * look at how to traverse the EEPROM.
 *
 * This example code is in the public domain.
 *
 * https://github.com/PaulStoffregen/EEPROM/blob/master/examples/eeprom_clear/eeprom_clear.ino
 */

#include <EEPROM.h>
#include "M5Atom.h"

void setup() {

  M5.begin(true, false, true);
  delay(50);

  /***
    Iterate through each byte of the EEPROM storage.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.
    - Teensy 3.0 & 3.1:   2kb EEPROM storage.
    - Teensy-LC:          128b EEPROM storage.
    - Teensy 2.0:         1kb EEPROM storage.
    - Teensy++ 2.0:       4kb EEPROM storage.


    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/

  // RED while erasing
  M5.dis.drawpix(0, 0xff0000);
  delay(3000);

  for (unsigned int i = 0; i < EEPROM.length(); i++)
    EEPROM.write(i, 0);

  // Green when complete
  M5.dis.drawpix(0, 0x00ff00);
}

void loop() { /** Empty loop. **/
}