#ifndef CONFIG_H
#define CONFIG_H

// Feature Flags
#define ENABLE_TFT true
#define ENABLE_SERIAL true
#define ENABLE_BLUETOOTH true
#define ENABLE_WIFI true
#define ENABLE_WEBSOCKETS true

// Button pin
#define BUTTON_PIN 0

// TFT display pins
// #define TFT_CS_PIN 4
// #define TFT_SDA_PIN 3
// #define TFT_SCL_PIN 5
// #define TFT_DC_PIN 2
// #define TFT_RES_PIN 1
// #define TFT_LEDA_PIN 38

// Default Settings
#define DEVICE_NAME "ESP32_Device"
#define WIFI_SSID "your_ssid"
#define WIFI_PASSWORD "your_password"
#define LOG_BUFFER_SIZE 256

#endif // CONFIG_H
