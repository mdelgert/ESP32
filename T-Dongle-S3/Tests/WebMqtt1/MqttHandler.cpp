#include <WiFi.h>
#include <PubSubClient.h>
#include "SecureConfig.h"
#include "MqttHandler.h" // Include the corresponding header

// Create an MQTT client object
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void initMqttClient() {
  // Set up the MQTT client
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);  // Use the declared callback function

  // Connect to MQTT broker and subscribe to the topic
  connectToMqtt();
}

void handleMqttClient() {
  // Reconnect to MQTT broker if disconnected
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  mqttClient.loop();
}

// Function to connect to MQTT broker and subscribe to the topic
void connectToMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (mqttClient.connect(DEFAULT_DEVICE_NAME, MQTT_USER, MQTT_PASSWORD)) {
      //Serial.println("connected");
      mqttClient.subscribe(MQTT_TOPIC);
      //Serial.print("Subscribed to topic: ");
      //Serial.println(MQTT_TOPIC);
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(mqttClient.state());
      //Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Callback function that handles incoming MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived on topic: ");
  //Serial.print(topic);
  //Serial.print(". Message: ");
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  //Serial.println(message);
  
  // Handle the message here (e.g., parse JSON, control hardware, etc.)
}

// Function to send a "hello" message to the MQTT topic
void sendHelloMessage() {
  // Create a JSON message
  String jsonMessage = "{\"message\": \"hello\"}";

  // Publish the message to the MQTT topic
  if (mqttClient.publish(MQTT_TOPIC, jsonMessage.c_str())) {
    //Serial.println("Hello message sent successfully.");
  } else {
    //Serial.println("Failed to send hello message.");
  }
}
