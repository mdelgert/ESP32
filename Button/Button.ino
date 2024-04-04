#include "M5Atom.h"

enum ButtonState { NOT_PRESSED, PRESSED, PRINTED };

ButtonState currentState = NOT_PRESSED;

void setup() {
    M5.begin(true, false, true);
    delay(50);
    M5.dis.drawpix(0, 0xff0000);
}

void loop() {
    if (M5.Btn.isPressed()) {
        M5.dis.drawpix(0, 0x0000f0);
        if (currentState == NOT_PRESSED) {
            currentState = PRESSED;    
            Serial.println("Keypressed!");
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
