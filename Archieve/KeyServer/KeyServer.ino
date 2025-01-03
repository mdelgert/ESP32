#include "M5Atom.h"
#include "KeySettings.h"
#include "KeyConfiguration.h"
#include "KeyWeb.h"

void setup() {
  M5.begin(true, false, true);
  checkData();
  delay(50);
  M5.dis.drawpix(0, 0x00ff00);  // GREEN
  keyWebSetup();
}

void loop() {
  if (M5.Btn.wasPressed()) {
    M5.dis.drawpix(0, 0xff0000);  // RED
    printSettings();
  } else {
    M5.dis.drawpix(0, 0x0000f0);  // BLUE
  }

  //delay(50);
  M5.update();
  configurationMenu();
  keyWebClient();
}