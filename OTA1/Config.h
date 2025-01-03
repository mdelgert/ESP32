#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
const char* WIFI_SSID = "Your_SSID";         // Replace with your WiFi SSID
const char* WIFI_PASSWORD = "Your_PASSWORD"; // Replace with your WiFi password

// Debug flags
#define DEBUG_TFT true
#define DEBUG_SERIAL true

// OTA Hostname
const char* HOST_NAME = "esp32-ota";
const char* OTA_PASSWORD = "123";

#endif // CONFIG_H
