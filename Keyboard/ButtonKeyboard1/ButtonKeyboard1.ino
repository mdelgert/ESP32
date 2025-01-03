#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

void setup() {
    USB.begin();          // Start USB functionality
    Keyboard.begin();     // Initialize HID keyboard
    delay(1000);          // Allow USB stack to initialize
}

void loop() {
    sendText("Hello World!");
    delay(5000);          // Wait 5 seconds before repeating
}

void sendText(const char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        Keyboard.write(text[i]); // Send one character at a time
        delay(20);               // Small delay between characters
    }
    Keyboard.write('\n');        // Add newline at the end
    delay(50);                   // Delay to ensure the newline is sent
}
