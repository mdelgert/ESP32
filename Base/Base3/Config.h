#ifndef CONFIG_H
#define CONFIG_H

// Feature Flags
#define ENABLE_TFT true
#define ENABLE_SERIAL false
#define ENABLE_WIFI true
#define ENABLE_WEBSOCKET true
#define ENABLE_SSL true
#define ENABLE_USB_HID true
#define ENABLE_MOUSE_JIGGLER false
#define ENABLE_BLUETOOTH_SERVER true

// Bluetooth Configuration
#define DEVICE_NAME "PassTxtBT"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Custom USB descriptors
#define CUSTOM_PRODUCT_NAME "USB KeyboardMouse"
#define CUSTOM_MANUFACTURER "PassTxtUsb"
#define CUSTOM_SERIAL_NUMBER "123456789"

// WebSocket Server URL
const char WEBSOCKET_URL[] = "wss://passtxtwebapidev2.azurewebsites.net/ws";

// Pin Definitions
#define BUTTON_PIN 0
#define LED_DI_PIN 40
#define LED_CI_PIN 39

// Default Settings
#define WIFI_SSID "CHANGEME"
#define WIFI_PASSWORD "CHANGEME"

#endif // CONFIG_H
