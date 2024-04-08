#include "M5Atom.h"
#include "BleMouse.h"

BleMouse bleMouse("Razer Mouse V3", "Razer Inc.", 100); // Create an instance of BleMouse with custom device name, manufacturer, and battery level

enum ButtonState { NOT_PRESSED,
                   PRESSED,
                   PRINTED };

ButtonState currentState = NOT_PRESSED;

bool mouseState = true;  // Declare and initialize mouseState
unsigned long timerDuration = 60000; // Default timer duration is 60 seconds (in milliseconds)
unsigned long lastMoveTime = 0; // Variable to store the time of the last mouse movement
unsigned long timerStartTime = 0; // Variable to store the start time of the timer
unsigned long jiggleX = 1; // Variable to store the amount to jiggle

void setup() {
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, 0xffffff);  // Set LED color to white
  delay(50);
  bleMouse.begin();
}

void loop() {
  if (M5.Btn.isPressed()) {
    M5.dis.drawpix(0, 0x0000f0);  // Set LED color to blue
    if (currentState == NOT_PRESSED) {
      currentState = PRESSED;
      if (mouseState == true) {
        mouseState = false;
        Serial.println("mouseState=false");
      } else {
        mouseState = true;
        Serial.println("mouseState=true");
        timerStartTime = millis(); // Record the start time of the timer
      }
    }
  } else {
    if (currentState == PRESSED) {
      currentState = PRINTED;
    } else if (currentState == PRINTED) {
      currentState = NOT_PRESSED;
      M5.dis.drawpix(0, 0xff0000);
    }
  }

  // Set LED color based on mouseState
  if (mouseState) {
    M5.dis.drawpix(0, 0x00ff00);  // Green color
    // Check if it's time to move the mouse
    unsigned long currentTime = millis();
    if (currentTime - timerStartTime >= timerDuration) {
      Serial.println("mouse jiggle");
      bleMouse.move(jiggleX, 0); // Move the mouse by 1 pixel in the x direction
      timerStartTime = currentTime; // Reset the timer start time
    }
  } else {
    M5.dis.drawpix(0, 0xff0000);  // Red color
  }

  // if(bleMouse.isConnected()) {
  //   Serial.println("Mouse connected");
  // }
  // else
  // {
  //   Serial.println("Mouse not connected.");
  // }

  delay(50);
  M5.update();
}
