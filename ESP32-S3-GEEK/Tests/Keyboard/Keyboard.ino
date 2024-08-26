#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

//Must hold reset to flash again in the future, mayrequire hold reset before plugging into USB port

void setup() {
  USB.begin();           // Start the USB stack
  delay(1000);           // Small delay to ensure the system is ready

  Keyboard.begin();      // Start the keyboard emulation
  delay(1000);           // Small delay to ensure the system is ready
  

  Keyboard.print("Hello");  // Send "Hello" as a keyboard input
  delay(5000);            // Small delay to ensure the message is sent
  
  Keyboard.end();        // End the keyboard emulation
}

void loop() {
}
