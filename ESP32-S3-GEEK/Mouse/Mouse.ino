#include "USB.h"
#include "USBHIDMouse.h"

USBHIDMouse Mouse;

//Must hold reset to flash again in the future, mayrequire hold reset before plugging into USB port

void setup() {
  USB.begin();      // Start the USB stack
  delay(1000);      // Small delay to ensure the system is ready

  Mouse.begin();    // Start the mouse emulation
}

void loop() {
  Mouse.move(5, 0); // Move mouse cursor 5 units to the right
  delay(500);       // Wait for half a second
  Mouse.move(-5, 0);// Move mouse cursor 5 units to the left
  delay(10000);       // Wait for half a second
}

