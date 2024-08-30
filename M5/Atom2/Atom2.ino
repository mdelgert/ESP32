#include "WebServerHandler.h"

void setup() {
  // Start Serial Monitor for debugging purposes
  Serial.begin(115200);

  // Initialize the web server and load any saved settings
  setupWebServer();

  Serial.println("Server started");
}

void loop() {
  // Handle incoming client requests to the web server
  handleWebServerClient();
}
