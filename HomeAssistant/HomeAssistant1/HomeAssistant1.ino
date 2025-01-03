#include <M5Atom.h>
#include "M5UnitENV.h"
#include <WiFi.h>
#include <PubSubClient.h>

// Define constants for pin configuration
const int SDA_PIN = 26;
const int SCL_PIN = 32;
const uint32_t I2C_FREQUENCY = 400000U;

// WiFi and MQTT configuration
#define WIFI_SSID "CHANGEME"
#define WIFI_PASSWORD "CHANGEME"
#define MQTT_DEVICE "temp1"
#define MQTT_BROKER "192.0.0.0"
#define MQTT_PORT 1883
#define MQTT_USER "CHANGEME"
#define MQTT_PASSWORD "CHANGEME"

const char* TEMP_TOPIC = ("homeassistant/sensor/" MQTT_DEVICE "/sht4x/state");
const char* ERROR_TOPIC = ("homeassistant/sensor/" MQTT_DEVICE "/error");

SHT4X sht4;
BMP280 bmp;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void initializeSensor(SHT4X& sensor, const char* sensorName) {
    if (!sensor.begin(&Wire, SHT40_I2C_ADDR_44, SDA_PIN, SCL_PIN, I2C_FREQUENCY)) {
        String errorMessage = String("Couldn't find ") + sensorName;
        Serial.println(errorMessage);
        mqttClient.publish(ERROR_TOPIC, errorMessage.c_str());
        while (1) delay(1);
    }
    sensor.setPrecision(SHT4X_HIGH_PRECISION);
    sensor.setHeater(SHT4X_NO_HEATER);
}

void connectToWiFi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi.");
}

void connectToMQTT() {
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    while (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");
        if (mqttClient.connect(MQTT_DEVICE, MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Connected to MQTT.");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(". Retrying in 5 seconds.");
            delay(5000);
        }
    }
}

void publishSensorData() {
    if (sht4.update()) {
        char payload[128];
        snprintf(payload, sizeof(payload), "{\"temperature\": %.2f, \"humidity\": %.2f}", sht4.cTemp, sht4.humidity);
        if (mqttClient.publish(TEMP_TOPIC, payload)) {
            Serial.println("Published sensor data successfully.");
        } else {
            Serial.println("Failed to publish sensor data.");
        }
    } else {
        String errorMessage = "SHT4x sensor update failed.";
        Serial.println(errorMessage);
        mqttClient.publish(ERROR_TOPIC, errorMessage.c_str());
    }
}

void registerDeviceWithHomeAssistant() {
    char configTopicTemp[128];
    char configTopicHum[128];

    snprintf(configTopicTemp, sizeof(configTopicTemp), "homeassistant/sensor/%s/temperature/config", MQTT_DEVICE);
    snprintf(configTopicHum, sizeof(configTopicHum), "homeassistant/sensor/%s/humidity/config", MQTT_DEVICE);

    char configPayloadTemp[512];
    char configPayloadHum[512];

    snprintf(configPayloadTemp, sizeof(configPayloadTemp),
        "{"
        "\"name\": \"Temperature\", "
        "\"state_topic\": \"%s\", "
        "\"unit_of_measurement\": \"°C\", "
        "\"value_template\": \"{{ value_json.temperature }}\", "
        "\"device_class\": \"temperature\", "
        "\"unique_id\": \"%s_temperature\", "
        "\"device\": {"
        "  \"identifiers\": [\"%s\"], "
        "  \"name\": \"%s\", "
        "  \"model\": \"SHT4x\", "
        "  \"manufacturer\": \"M5Stack\""
        "}"
        "}",
        TEMP_TOPIC, MQTT_DEVICE, MQTT_DEVICE, MQTT_DEVICE);

    snprintf(configPayloadHum, sizeof(configPayloadHum),
        "{"
        "\"name\": \"Humidity\", "
        "\"state_topic\": \"%s\", "
        "\"unit_of_measurement\": \"%%\", "
        "\"value_template\": \"{{ value_json.humidity }}\", "
        "\"device_class\": \"humidity\", "
        "\"unique_id\": \"%s_humidity\", "
        "\"device\": {"
        "  \"identifiers\": [\"%s\"], "
        "  \"name\": \"%s\", "
        "  \"model\": \"SHT4x\", "
        "  \"manufacturer\": \"M5Stack\""
        "}"
        "}",
        TEMP_TOPIC, MQTT_DEVICE, MQTT_DEVICE, MQTT_DEVICE);

    mqttClient.publish(configTopicTemp, configPayloadTemp, true);
    mqttClient.publish(configTopicHum, configPayloadHum, true);
}

void setup() {
    M5.begin(true, false, true); // Initialize M5 Atom-Matrix with Serial and LED support
    delay(50);
    M5.dis.drawpix(0, 0x00ff00);

    Serial.begin(115200);
    //delay(1000);

    connectToWiFi();

    // Increase MQTT buffer size
    mqttClient.setBufferSize(512);
    connectToMQTT();

    registerDeviceWithHomeAssistant();

    initializeSensor(sht4, "SHT4x");
}

void loop() {
    if (!mqttClient.connected()) {
        connectToMQTT();
    }
    mqttClient.loop();

    publishSensorData();
    delay(1000);
}
