#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

// Global variables for the reusable function
unsigned long previousMillis = 0;  // Tracks the last key write time
const unsigned long interval = 100; // Default interval between key presses

void setup() {
  USB.begin();
  Keyboard.begin();

  // Non-blocking USB initialization delay
  unsigned long startTime = millis();
  while (millis() - startTime < 2000) {
    // Do nothing while USB initializes
  }
}

void loop() {
  // Call reusable function to send "hello" repeatedly
  //sendStringNonBlocking("hello\n", interval);
  sendStringNonBlocking("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc dignissim pharetra dui, ac luctus nunc sodales a. Etiam urna tortor, blandit finibus congue ut, consequat non libero.\n", interval);
  // Add other non-blocking tasks here
}

// Reusable function to send a string with non-blocking delays
void sendStringNonBlocking(const char* message, unsigned long delayInterval) {
  static size_t messageIndex = 0;  // Tracks the current character in the string
  unsigned long currentMillis = millis();

  // Check if it's time to send the next key
  if (currentMillis - previousMillis >= delayInterval) {
    previousMillis = currentMillis; // Update the last write time

    // Send the current character
    if (message[messageIndex] != '\0') {
      Keyboard.write(message[messageIndex]);
      messageIndex++; // Move to the next character
    } else {
      messageIndex = 0; // Reset index to repeat the string
    }
  }
}
