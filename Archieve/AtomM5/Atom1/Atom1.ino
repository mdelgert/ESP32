#include <M5Atom.h>

void setup() {
    M5.begin(true, false,true); // Init Atom-Matrix(Initialize serial port and LED not necessary to set speed as M5Atom.h does this).
    delay(50);
    M5.dis.drawpix(0, 0x00ff00);
}

void loop() {
    Serial.print("Test");
    delay(1000);
}