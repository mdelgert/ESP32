#include "M5Atom.h"
#include "BleCombo.h"

enum ButtonState { NOT_PRESSED, PRESSED, PRINTED };

ButtonState currentState = NOT_PRESSED;

void setup() {
    M5.begin(true, false, true);
    delay(50);
    M5.dis.drawpix(0, 0xff0000);
    Keyboard.begin();
    Mouse.begin();
}

void loop() {
    if (M5.Btn.isPressed()) {
        M5.dis.drawpix(0, 0x0000f0);
        if (currentState == NOT_PRESSED) {
            currentState = PRESSED;    
            Serial.println("Keypressed!");
            //Keyboard.println("Hello1~!@#$%^&*()");
            Keyboard.print("Hello1~!@#$%^&*()");
            Keyboard.releaseAll();
            delay(1000);
            Mouse.move(10,0);
            delay(1000);
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

