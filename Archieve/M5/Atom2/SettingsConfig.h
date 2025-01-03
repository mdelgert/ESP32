#ifndef CONFIG_H
#define CONFIG_H

// Default configuration values for setup_mode = true
#define SETUP_MODE true
#define DEFAULT_SSID "ESP32WAP"
#define DEFAULT_PASSWORD "12345678"
#define DEFAULT_DEVICE_NAME "atom1"
#define DEFAULT_ADMIN "admin"
#define DEFAULT_ADMIN_PASSWORD "password"

// Default network configuration for Access Point mode
#define DEFAULT_LOCAL_IP IPAddress(192, 168, 4, 1)
#define DEFAULT_GATEWAY IPAddress(192, 168, 4, 1)
#define DEFAULT_SUBNET IPAddress(255, 255, 255, 0)

// Default mqtt configuration
#define MQTT_BROKER "example.emqx.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic/1"
#define MQTT_USER "user"
#define MQTT_PASSWORD "password"
#define MQTT_CERTIFICATE_ENABLE false
#define MQTT_CERTIFICATE ""

#endif // CONFIG_H
