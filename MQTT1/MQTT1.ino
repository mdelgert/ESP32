#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi and MQTT settings
const char* ssid = "yourssid";
const char* password = "yourpassword";
const char* mqttServer = "192.168.50.174";
const int mqttPort = 1883;
const char* mqttTopic = "testtopic/test";
const char* mqttUser = "emqx";
const char* mqttPassword = "public";

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Message counter and timing variables
unsigned long previousMillis = 0;
const unsigned long interval = 3000; // 3 seconds
int messageCounter = 1; // Start from Test1

void setup() {
    Serial.begin(115200);
    delay(100);

    // Connect to Wi-Fi
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");

    // Configure MQTT client
    mqttClient.setServer(mqttServer, mqttPort);

    // Connect to MQTT broker
    if (mqttClient.connect("ESP32TestClientTest", mqttUser, mqttPassword)) {
        Serial.println("Connected to MQTT broker");
    } else {
        Serial.println("Failed to connect to MQTT broker. Check username/password.");
    }
}

void loop() {
    // Maintain MQTT connection

    if (!mqttClient.connected()) {
        if (mqttClient.connect("ESP32TestClient", mqttUser, mqttPassword)) {
            // Subscribe only once
            mqttClient.subscribe(mqttTopic);
            Serial.println("Subscribed to topic: " + String(mqttTopic));
        }
    }

    mqttClient.loop();

    // Publish a message every 3 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Create the message
        String message = "Test" + String(messageCounter);
        messageCounter++; // Increment the counter for the next message

        // Publish the message
        if (mqttClient.publish(mqttTopic, message.c_str())) {
            Serial.println("Message published: " + message);
        } else {
            Serial.println("Failed to publish message");
        }
    }
}
