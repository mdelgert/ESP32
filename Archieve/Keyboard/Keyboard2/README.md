arduino-cli lib install "Adafruit TinyUSB Library"@3.1.1

If you're experiencing inconsistent behavior with the `USBHIDKeyboard.h` library on your ESP32-S3, here are some alternative libraries and strategies to consider:

### Alternative Libraries
1. **`TinyUSB` (Espressif Fork):**
   Espressif's integration of `TinyUSB` is the most robust and officially supported USB library for the ESP32-S3. It provides HID support, including keyboard functionalities. 
   - **Advantages**: Actively maintained, highly compatible, and optimized for ESP32-S3 hardware.
   - **Documentation**: [TinyUSB on ESP32-S3](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/peripherals/usb.html)
   - To use it:
     - Install the ESP-IDF or the Arduino-ESP32 core (if you aren't already using it).
     - Use the example projects for USB HID in the `TinyUSB` examples section.

2. **Adafruit TinyUSB Library:**
   Adafruit maintains a version of the `TinyUSB` library for Arduino that works with ESP32-S3.
   - Install it from the Arduino Library Manager (`Adafruit TinyUSB Library`).
   - Check examples under **File -> Examples -> Adafruit TinyUSB Library -> USB HID -> Keyboard**.

### Why `TinyUSB` Is Better:
- It is actively maintained and supports advanced USB features such as composite devices, better HID customization, and more robust handling of USB descriptors.
- It supports USB HID out of the box with highly configurable endpoints and input methods.

---

### Debugging `USBHIDKeyboard.h` Issues
If you prefer to continue using `USBHIDKeyboard.h`, try these steps to improve its performance:

1. **Update the Library**: Ensure you have the latest version of the `USBHIDKeyboard` library and the Arduino-ESP32 core.

2. **Power and Connections**:
   - Make sure the ESP32-S3 is receiving adequate power. USB-HID operations can be sensitive to voltage fluctuations.
   - Test with different USB cables and ports.

3. **Proper Initialization**:
   - Double-check that the library is correctly initialized in your code and that you’re using the appropriate `begin()` methods.

4. **Driver Conflicts**:
   - On Windows, Linux, or macOS, ensure there are no driver conflicts. Sometimes, older USB drivers can interfere with HID devices.

5. **Serial Debugging**:
   - Add debugging to your code to capture any issues in initialization or runtime.

---

### Switching to `TinyUSB`
Here’s a minimal example to get started with `TinyUSB`:

```cpp
#include <Adafruit_TinyUSB.h>

Adafruit_USBD_HID usb_hid;

void setup() {
  Serial.begin(115200);
  usb_hid.setPollInterval(2); // Faster polling
  usb_hid.keyboardReport(0, 0, NULL); // Initial report
  usb_hid.begin();
  
  while (!Serial) {
    delay(10); // Wait for Serial Monitor to open
  }
  Serial.println("HID Keyboard Initialized!");
}

void loop() {
  uint8_t keycode[6] = {HID_KEY_A}; // Send 'A' key
  usb_hid.keyboardReport(0, HID_KEY_SHIFT_LEFT, keycode);
  delay(100);
  usb_hid.keyboardRelease();
  delay(1000);
}
```

---

### Next Steps
If `TinyUSB` also has issues, it could be related to:
- Hardware compatibility.
- USB host devices not handling HID reports correctly.
- Bugs in the ESP32-S3 USB stack (ensure you're using the latest ESP-IDF/Arduino core).

Feel free to share your specific use case or issues for further guidance!

Name: "Adafruit TinyUSB Library"
  Author: Adafruit
  Maintainer: Adafruit <info@adafruit.com>
  Sentence: TinyUSB library for Arduino
  Paragraph: Support nRF5x, SAMD21, SAMD51, RP2040, ESP32-S2/S3, CH32V
  Website: https://github.com/adafruit/Adafruit_TinyUSB_Arduino
  Category: Communication
  Architecture: *
  Types: Contributed
  Versions: [0.0.1, 0.5.0, 0.6.0, 0.7.0, 0.7.1, 0.8.0, 0.8.1, 0.8.2, 0.9.0, 0.9.1, 0.10.0, 0.10.1, 0.10.2, 0.10.4, 0.10.5, 1.0.0, 1.0.1, 1.0.3, 1.1.0, 1.3.0, 1.3.1, 1.3.2, 1.3.3, 1.4.0, 1.4.1, 1.4.2, 1.4.3, 1.4.4, 1.5.0, 1.6.0, 1.7.0, 1.7.1, 1.8.0, 1.9.0, 1.9.1, 1.9.2, 1.9.3, 1.9.4, 1.10.0, 1.10.1, 1.10.2, 1.10.3, 1.11.0, 1.12.0, 1.13.1, 1.13.2, 1.13.3, 1.14.0, 1.14.1, 1.14.2, 1.14.3, 1.14.4, 1.16.0, 1.17.0, 1.17.1, 1.18.0, 1.18.1, 1.18.3, 1.18.4, 2.0.0, 2.0.1, 2.0.2, 2.0.3, 2.1.0, 2.2.0, 2.2.1, 2.2.2, 2.2.3, 2.2.4, 2.2.5, 2.2.6, 2.2.7, 2.2.8, 2.3.0, 2.3.1, 2.3.2, 2.3.3, 2.4.0, 2.4.1, 3.0.0, 3.1.0, 3.1.1, 3.1.3, 3.1.4, 3.1.5, 3.2.0, 3.3.0, 3.3.1, 3.3.2, 3.3.3, 3.3.4, 3.4.0, 3.4.1, 3.4.2]
  Provides includes: Adafruit_TinyUSB.h
  Dependencies: Adafruit SPIFlash, MIDI Library, SdFat - Adafruit Fork