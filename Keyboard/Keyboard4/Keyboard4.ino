#include "keyboard.h" // Include the HIDKeyboard library
#include "locales.h"  // For handling locales like US keyboards
// #include "USBHID.h"    // Ensure USB HID support
#include "USB.h"

HIDKeyboard keyboard; // Instantiate the HIDKeyboard class

void setup()
{
    Serial.begin(115200);

    // Initialize HID Keyboard
    keyboard.begin();
    keyboard.setLocale(&locale_us); // Use US locale (customize if needed)
    USB.begin();
    delay(200);

    // Optional: Register event handler
    //keyboard.onEvent(ARDUINO_USB_HID_KEYBOARD_LED_EVENT, handleKeyboardEvent);

    // Small delay to ensure the HID connection is established
    delay(2000);
}

void loop()
{
    // Step 1: Type "Hello"
    //keyboard.write("Hello");
    //keyboard.pressKey(KEY_ENTER); // Press 'Enter' after "Hello"
    //keyboard.release();
    //delay(1000); // Short delay before the next action

    // Step 2: Lock the computer (Win+L)
    keyboard.pressModifier(KEY_MOD_LMETA); // Press 'Win' key
    //keyboard.pressKey('l');                // Press 'L' key
    //delay(50);                             // Hold keys briefly
    //keyboard.release();                    // Release all keys

    delay(5000); // Wait 5 seconds before repeating
}

// Event handler for keyboard events (optional)
void handleKeyboardEvent(void *handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    arduino_usb_hid_keyboard_event_data_t *data = (arduino_usb_hid_keyboard_event_data_t *)event_data;

    if (event_id == ARDUINO_USB_HID_KEYBOARD_LED_EVENT)
    {
        Serial.print("Keyboard LED Event - NumLock: ");
        Serial.print(data->numlock);
        Serial.print(", CapsLock: ");
        Serial.print(data->capslock);
        Serial.print(", ScrollLock: ");
        Serial.println(data->scrolllock);
    }
}
