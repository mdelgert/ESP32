#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

const int delayTime = 5000; // Delay time in milliseconds

// Function to send a string and press return
void sendString(const char* str) {
    while (*str) {
        Keyboard.write(*str); // Write each character
        delay(10);            // Small delay between characters for stability
        str++;
    }
    Keyboard.write('\n');     // Send a return (Enter key)
}

void lockWindows() {
    Keyboard.press(KEY_LEFT_GUI); // Press Windows key
    Keyboard.press('l');          // Press 'L'
    delay(100);                   // Short delay
    Keyboard.releaseAll();        // Release all keys
}


void setup() {
    // Initialize USB HID keyboard
    Keyboard.begin();

    // Start the USB device
    USB.begin();

    // Delay to ensure USB enumeration is complete
    delay(2000); // 2 seconds for host to recognize the device
}

void loop() {
    // Use the custom function to send a string
    sendString("Hello, world!");

    // Delay before sending the next message
    delay(delayTime);

    lockWindows();
}
