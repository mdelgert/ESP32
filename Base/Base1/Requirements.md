I'm a .NET programmer adapting to C++ for Arduino projects. I aim to keep the main sketch concise by centralizing reusable logic. I have an Arduino C++ project for an ESP32 microcontroller. I want a single method for printing messages with feature switches for outputting to Serial or `TFT_eSPI.h`. My projects will utilize libraries such as `FastLED.h`, `WiFi.h`, `ArduinoWebsockets.h`, `NimBLEDevice.h`, `Preferences.h`, `USBHIDKeyboard.h`, and `USBHIDMouse.h`.

I plan to centralize configuration and pin settings, with feature flags to enable specific features and initiate them. Default values should be centralized, but if a user saves settings to `Preferences.h`, those values should take precedence. All features should integrate with the centralized message printing method.

Additionally, I need callbacks for Bluetooth and WebSockets to process JSON messages, triggering actions like turning on LEDs, moving the mouse, sending keypresses, printing messages to the TFT, or saving settings to `Preferences.h`.

Please provide starter template for me to use the follows best practices and any other recommendations. Where these features can call each other and have a clean sketch. Include features for TFT, FASTLED, Wifi, Bluetooth, Button, USBHIDMouse and USBHIDKeyboard.

1. **Organizing the structure:** Code into reusable functions, classes, or modules for better readability and maintainability.
2. **Improving variable and function names:** Use descriptive, consistent naming conventions.
3. **Optimizing memory usage:** Use `PROGMEM` for constants where appropriate and reduce global variable usage.
4. **Enhancing readability:** Remove redundant code, add meaningful comments, and ensure consistent formatting (e.g., proper indentation and braces alignment).
5. **Adding error handling:** Include robust checks for operations like Wi-Fi connections, WebSocket setup, and SSL loading.
6. **Minimizing blocking calls:** Replace `delay()` with non-blocking logic using `millis()` for multitasking.
7. **Following Arduino best practices:** Keep the `loop()` function simple and delegate tasks to helper functions or classes.
8. **Separating configuration:** Move constants (like credentials, URLs, and retry delays) to a configuration file.
9. **Including debugging support:** Add optional debug logs controlled by preprocessor directives.
10. Add the file name to head of each file.
