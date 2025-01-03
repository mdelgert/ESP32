#ifndef KEYBOARD_MOUSE_HANDLER_H
#define KEYBOARD_MOUSE_HANDLER_H

#include "USB.h"
#include "USBHIDKeyboard.h"
#include "USBHIDMouse.h"
#include "LogManager.h"
#include "Config.h"
#include "tusb.h" // Include TinyUSB library for custom descriptor

class KeyboardMouseHandler {
private:
    static USBHIDKeyboard keyboard;
    static USBHIDMouse mouse;
    static bool initialized;

public:
    // Initialize USB HID Keyboard and Mouse
    static void init() {
        if (!ENABLE_USB_HID) {
            LogManager::log("USB HID is disabled (ENABLE_USB_HID is false).");
            return;
        }

        if (initialized) {
            LogManager::log("KeyboardMouseHandler already initialized.");
            return;
        }

        LogManager::log("Initializing USB HID Keyboard and Mouse...");
        USB.begin();    // Start USB stack
        keyboard.begin(); // Start keyboard
        mouse.begin();   // Start mouse

        initialized = true;
        LogManager::log("USB HID Keyboard and Mouse initialized.");
    }

    // Send a single key press
    static void sendKeyPress(uint8_t key) {
        if (!ENABLE_USB_HID) {
            LogManager::log("USB HID is disabled.");
            return;
        }

        if (!initialized) {
            LogManager::log("KeyboardMouseHandler not initialized.");
            return;
        }

        LogManager::log(String("Sending key press: ") + char(key));
        keyboard.press(key);
        delay(50);
        keyboard.release(key);
    }

    // Send a string of keys
    static void sendKeys(const char* text) {
        if (!ENABLE_USB_HID) {
            LogManager::log("USB HID is disabled.");
            return;
        }

        if (!initialized) {
            LogManager::log("KeyboardMouseHandler not initialized.");
            return;
        }

        LogManager::log("Sending keys: " + String(text));
        for (int i = 0; text[i] != '\0'; i++) {
            keyboard.write(text[i]); // Send character as a key
            delay(20);
        }
        keyboard.write('\n'); // Optional newline
        delay(50);
    }

    // Send mouse movement
    static void sendMouseMove(int8_t x, int8_t y, int8_t wheel = 0) {
        if (!ENABLE_USB_HID) {
            LogManager::log("USB HID is disabled.");
            return;
        }

        if (!initialized) {
            LogManager::log("KeyboardMouseHandler not initialized.");
            return;
        }

        LogManager::log(String("Moving mouse: X=") + x + ", Y=" + y + ", Wheel=" + wheel);
        mouse.move(x, y, wheel);
    }

    // Perform a mouse click
    static void sendMouseClick(uint8_t button) {
        if (!ENABLE_USB_HID) {
            LogManager::log("USB HID is disabled.");
            return;
        }

        if (!initialized) {
            LogManager::log("KeyboardMouseHandler not initialized.");
            return;
        }

        LogManager::log("Clicking mouse button.");
        mouse.click(button);
    }

    // Return initialization status
    static bool isInitialized() {
        return initialized;
    }

    // Access the mouse instance
    static USBHIDMouse& getMouse() {
        return mouse;
    }
};

// Static member definitions
USBHIDKeyboard KeyboardMouseHandler::keyboard;
USBHIDMouse KeyboardMouseHandler::mouse;
bool KeyboardMouseHandler::initialized = false;

// Custom string descriptor callback for HID device
extern "C" const uint16_t* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    static uint16_t descriptor[32]; // Buffer for UTF-16 string
    const char* string = nullptr;

    switch (index) {
        case 0: // Language ID
            descriptor[0] = (TUSB_DESC_STRING << 8) | (2 * 1 + 2); // Length of descriptor and type
            descriptor[1] = 0x0409; // English (United States) language ID
            return descriptor;
        case 1: // Product Name
            string = CUSTOM_PRODUCT_NAME;
            break;
        case 2: // Manufacturer Name
            string = CUSTOM_MANUFACTURER;
            break;
        case 3: // Serial Number
            string = CUSTOM_SERIAL_NUMBER;
            break;
        default:
            return nullptr;
    }

    // Convert ASCII to UTF-16
    if (string) {
        size_t len = strlen(string);
        if (len > 31) len = 31; // Limit to 31 characters
        descriptor[0] = (TUSB_DESC_STRING << 8) | (2 * len + 2); // Length and type
        for (size_t i = 0; i < len; i++) {
            descriptor[i + 1] = string[i];
        }
        return descriptor;
    }

    return nullptr;
}

#endif // KEYBOARD_MOUSE_HANDLER_H
