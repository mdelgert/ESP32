//.arduino15/packages/esp32/hardware/esp32/2.0.17/tools/sdk/esp32s2/include/arduino_tinyusb/tinyusb/src/class/hid/hid.h

#include "USB.h"
#include "USBHIDKeyboard.h"
// #include "class/hid/hid.h"

USBHIDKeyboard Keyboard;

// Function prototype
void sendStringWithNonBlockingDelay(const char *str, unsigned long interval);

void setup()
{
    USB.begin();
    Keyboard.begin();
}

void loop()
{
    // Keyboard.write('h');
    // delay(20);
    // Keyboard.releaseAll();
    // Keyboard.press(KEY_LEFT_GUI);

    // https://github.com/espressif/arduino-esp32/issues/8380
    // Keyboard.press(HID_KEY_GUI_LEFT);
    // delay(3000);
    // Keyboard.releaseAll();

    // Works with ESP32 ###########################################################
    // Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    // Keyboard.pressRaw(HID_KEY_R);
    // delay(500);
    // Keyboard.releaseRaw(HID_KEY_GUI_LEFT);
    // Keyboard.releaseRaw(HID_KEY_R);
    // Keyboard.printf("notepad\n");
    // Works with ESP32 ###########################################################

    // Keyboard.printf("hello\n");
    // sendStringWithDelay("notepad");

    unsigned long startTime = millis();

    while (millis() - startTime < 2000)
    {
        // Wait for USB initialization without locking
    }

    // Send "notepad" with non-blocking delay
    sendStringWithNonBlockingDelay("notepad\n", 100);
    // Keyboard.pressRaw(HID_KEY_RETURN);
    // delay(500);
    // Keyboard.releaseAll();
    delay(3000);
}

// Non-blocking function to send a string with delays
void sendStringWithNonBlockingDelay(const char *str, unsigned long interval)
{
    static unsigned long previousMillis = 0;
    static const char *currentChar = str;

    while (*currentChar)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            Keyboard.write(*currentChar); // Send one character
            currentChar++;                // Move to the next character
        }
    }
}

// Function to send a string with delays using Keyboard.write()
void sendStringWithDelay(const char *str)
{
    while (*str)
    {
        Keyboard.write(*str); // Send one character
        delay(100);           // 100ms delay to ensure consistency
        str++;                // Move to the next character
    }
}