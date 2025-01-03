#include "USB.h"
#include "USBHIDKeyboard.h"
#include "tusb.h"

// Define custom USB product name, manufacturer, and serial number
#define CUSTOM_PRODUCT_NAME "My_Custom_Keyboard"
#define CUSTOM_MANUFACTURER "My_Keyboard_Manufacturer"
#define CUSTOM_SERIAL_NUMBER "1234567890"

// USB HID Keyboard instance
USBHIDKeyboard Keyboard;

// Custom string descriptor callback
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

void setup() {
    // Initialize Serial for debugging
    Serial.begin(115200);
    Serial.println("Starting USB HID Keyboard example...");

    // Initialize USB
    USB.begin();
    Keyboard.begin();

    Serial.println("USB HID Keyboard is ready");
}

void loop() {
    /*
    // Simple demonstration: send keypress periodically
    delay(1000);
    Keyboard.press(65); // ASCII value for 'A'
    delay(100);
    Keyboard.release(65); // Release key 'A'
    Serial.println("Key 'A' pressed and released");
    */
}
