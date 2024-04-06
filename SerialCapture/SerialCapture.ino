//https://www.norwegiancreations.com/2017/12/arduino-tutorial-serial-inputs/
//https://espblockly.com/SerialInputOutput.html

#include "M5Atom.h"

String my_name;

void setup() {
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, 0x0000f0);
  Serial.println("What is your name?");
}

void loop() {
  if (Serial.available()) {
    my_name = Serial.readStringUntil('\n');

    Serial.println("Nice to meet you, " + my_name + "!");
  }
}
