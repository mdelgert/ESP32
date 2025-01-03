#include "M5Atom.h"
// #include <FastLED.h>
#include <WiFi.h>
#include "SecureConfig.h"     // Include the SecureConfig.h file
#include "WebServerHandler.h" // Include the WebServerHandler header
#include "MqttHandler.h"      // Include the MqttHandler header

void setup()
{
  M5.begin(true, false, true);
  M5.dis.fillpix(0xFFFFFF); // WHITE

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(DEFAULT_SSID);
  WiFi.begin(DEFAULT_SSID, DEFAULT_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    M5.dis.fillpix(0xFFFF00); // YELLOW
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

void loop()
{
  // Handle web server requests
  handleWebServerClient();

  // Handle MQTT client tasks
  handleMqttClient();

  // Check if the button was pressed
  if (M5.Btn.wasPressed())
  {
    Serial.println("Button was pressed!");
    sendHelloMessage(); // Send a "hello" message to the MQTT topic
  }

  delay(50);
  M5.update();
}
