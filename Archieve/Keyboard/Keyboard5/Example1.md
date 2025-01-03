#include "USBHIDKeyboard.h"

// Initialize the HID Keyboard
USBHIDKeyboard Keyboard;

// Function prototype
void sendStringWithNonBlockingDelay(const char* str, unsigned long interval);

void setup() {
  // Start USB and Keyboard
  USB.begin();
  Keyboard.begin();
  
  unsigned long startTime = millis();
  while (millis() - startTime < 2000) {
    // Wait for USB initialization without locking
  }

  // Simulate 'Win + R' to open the Run dialog
  Keyboard.pressRaw(HID_KEY_GUI_LEFT);
  Keyboard.pressRaw(HID_KEY_R);
  delay(500); // You can replace this too if needed
  Keyboard.releaseRaw(HID_KEY_GUI_LEFT);
  Keyboard.releaseRaw(HID_KEY_R);

  // Send "notepad" with non-blocking delay
  sendStringWithNonBlockingDelay("notepad", 100);

  // Press Enter
  Keyboard.write('\n');
}

void loop() {
  // Other tasks can go here
}

// Non-blocking function to send a string with delays
void sendStringWithNonBlockingDelay(const char* str, unsigned long interval) {
  static unsigned long previousMillis = 0;
  static const char* currentChar = str;

  while (*currentChar) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      Keyboard.write(*currentChar); // Send one character
      currentChar++;               // Move to the next character
    }
  }
}
