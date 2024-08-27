//Requires PubSubClient and ArduinoJson Library
//https://www.arduino.cc/reference/en/libraries/pubsubclient/
//https://www.arduino.cc/reference/en/libraries/arduinojson/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "SSID";
const char* password = "*pass";
const char* mqtt_server = "server";
const int mqtt_port = 8883;
const char* mqtt_user = "test";
const char* mqtt_password = "password";
const char* mqtt_topic = "device1/actions";

const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"YOUR CERT HERE\n" \
"-----END CERTIFICATE-----\n";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void sendJsonMessage() {
    StaticJsonDocument<200> doc;
    doc["action"] = "message";
    doc["message"]["Line1"] = "Hello world1";

    char buffer[256];
    size_t n = serializeJson(doc, buffer);
    client.publish(mqtt_topic, buffer, n);
}

void setup() {
    Serial.begin(115200);
    setup_wifi();

    espClient.setCACert(ca_cert);
    client.setServer(mqtt_server, mqtt_port);

    reconnect();
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }

    sendJsonMessage();  // Send the message in a loop

    client.loop();  // Maintain MQTT connection and process incoming messages

    delay(1000);  // Delay 1 second between messages
}
