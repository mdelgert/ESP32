#include "M5Atom.h"
//#include <FastLED.h>
#include <WiFi.h>
#include "SecureConfig.h"       // Include the SecureConfig.h file
#include "WebServerHandler.h"   // Include the WebServerHandler header
#include "MqttHandler.h"        // Include the MqttHandler header

void setup() {
  M5.begin(true, false, true);
  // M5.dis.drawpix(0, 0x0000f0);  // BLUE
  // M5.dis.fillpix(0xff0000);  // RED
  // M5.dis.fillpix(0x00ff00);  // GREEN
  // M5.dis.fillpix(0xfff000);  // YELLOW
  M5.dis.fillpix(0xFFFFFF); //WHITE
  
  // Start serial communication
  //Serial.begin(115200);

  // Connect to Wi-Fi
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

  // Initialize the web server
  initWebServer();

  // Initialize MQTT client
  initMqttClient();
}

void loop() {
  // Handle web server requests
  handleWebServerClient();

  // Handle MQTT client tasks
  handleMqttClient();
}
