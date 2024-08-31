#ifndef CONFIG_H
#define CONFIG_H

// Default configuration values for setup_mode = true
#define SETUP_MODE true
#define DEFAULT_SSID "ESP32WAP"
#define DEFAULT_PASSWORD "12345678"
#define DEFAULT_DEVICE_NAME "atom1"
#define DEFAULT_ADMIN "admin"
#define DEFAULT_ADMIN_PASSWORD "password"

// Default mqtt configuration
#define MQTT_BROKER "example.emqx.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic/1"
#define MQTT_USER "user"
#define MQTT_PASSWORD "password"
#define MQTT_CERTIFICATE_ENABLE false
#define MQTT_CERTIFICATE ""

// Web server configuration
#define SERVER_PORT 80

// Firmware version
#define FIRMWARE_VERSION "1.0.0"

#endif // CONFIG_H
