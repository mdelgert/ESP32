#include "KeySettings.h"
#include "M5Atom.h"

void setup() {
  M5.begin(true, false, true);
  checkData();
  delay(50);
  M5.dis.drawpix(0, 0xff0000);
  saveSettings();
}

void loop() {
  delay(1000);
  printSettings();
}
