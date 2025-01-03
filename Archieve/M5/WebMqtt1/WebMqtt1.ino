#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include "SecureConfig.h" // Include the SecureConfig.h header file

// Create a web server object that listens for HTTP requests on the configurable port
WebServer server(SERVER_PORT);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi using settings from SecureConfig.h
  Serial.print("Connecting to ");
  Serial.println(DEFAULT_SSID);
  WiFi.begin(DEFAULT_SSID, DEFAULT_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the MQTT client
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  // Connect to MQTT broker and subscribe to the topic
  connectToMqtt();

  // Define the REST API endpoint and associate it with a function
  server.on("/settings/about", HTTP_GET, handleAbout); // When a GET request is made to /settings/about, call handleAbout function
  
  // Start the server
  server.begin();
  Serial.print("HTTP API server started on port ");
  Serial.println(SERVER_PORT);
}

void loop() {
  // Handle client requests for the web server
  server.handleClient();

  // Reconnect to MQTT broker if disconnected
  if (!mqttClient.connected()) {
    connectToMqtt();
  }
  mqttClient.loop();
}

// Function to handle GET requests to the "/settings/about" endpoint
void handleAbout() {
  // Create a JSON response with the firmware version
  String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";

  // Send the JSON response
  server.send(200, "application/json", jsonResponse);
}

// Function to connect to MQTT broker and subscribe to the topic
void connectToMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (mqttClient.connect(DEFAULT_DEVICE_NAME, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      mqttClient.subscribe(MQTT_TOPIC);
      Serial.print("Subscribed to topic: ");
      Serial.println(MQTT_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Callback function that handles incoming MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
  
  // Handle the message here (e.g., parse JSON, control hardware, etc.)
}
