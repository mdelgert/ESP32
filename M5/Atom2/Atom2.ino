#include <WiFi.h>
#include "WebServerHandler.h"

// Replace with your network credentials
const char* ssid = "ESP32_AccessPoint";
const char* password = "12345678";

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as an access point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Initialize the web server and print saved settings
  setupWebServer();

  Serial.println("Server started");
}

void loop() {
  // Handle client requests
  handleWebServerClient();
}
