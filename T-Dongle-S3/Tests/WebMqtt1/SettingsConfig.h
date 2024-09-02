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

// Board pins
#define FASTLED_INTERNAL //remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#define BTN_PIN        0
#define LED_DI_PIN     40
#define LED_CI_PIN     39
#define TFT_CS_PIN     4
#define TFT_SDA_PIN    3
#define TFT_SCL_PIN    5
#define TFT_DC_PIN     2
#define TFT_RES_PIN    1
#define TFT_LEDA_PIN   38
#define SD_MMC_D0_PIN  14
#define SD_MMC_D1_PIN  17
#define SD_MMC_D2_PIN  21
#define SD_MMC_D3_PIN  18
#define SD_MMC_CLK_PIN 12
#define SD_MMC_CMD_PIN 16
#endif // CONFIG_H
