#include "M5Atom.h"
#include "AtomSocket.h"

#define RXD   22
#define RELAY 23

ATOMSOCKET ATOM;

HardwareSerial AtomSerial(2);

bool RelayFlag = false;

void setup() {
    M5.begin(true, false, true);
    delay(1000);
    ATOM.Init(AtomSerial, RELAY, RXD);
    Serial.println("ATOM started");
}

void loop() {
    if (M5.Btn.wasPressed()) {
        RelayFlag = !RelayFlag;
        Serial.println("Button Pressed");
    }
    if (RelayFlag) {
        M5.dis.drawpix(0, 0x00ff00);
        ATOM.SetPowerOn();
    } else {
        ATOM.SetPowerOff();
        M5.dis.drawpix(0, 0xff0000);
    }
    M5.update();
}
