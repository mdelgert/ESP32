#ifndef CONFIG_H
#define CONFIG_H

// Feature Flags
#define ENABLE_SERIAL true
#define ENABLE_TFT true
#define ENABLE_BLUETOOTH true
#define ENABLE_WEBSOCKETS true

// Pins
constexpr int LED_PIN = 2;

// Default Configuration
#define DEFAULT_WIFI_SSID "YourSSID"
#define DEFAULT_WIFI_PASSWORD "YourPassword"

// Debugging
#define DEBUG true

#endif
