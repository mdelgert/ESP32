#include <WiFi.h>
#include <WebServer.h>
#include "SecureConfig.h" // Include the SecureConfig.h header file

// Create a web server object that listens for HTTP requests on the configurable port
WebServer server(SERVER_PORT);

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

  // Define the REST API endpoint and associate it with a function
  server.on("/settings/about", HTTP_GET, handleAbout); // When a GET request is made to /settings/about, call handleAbout function
  
  // Start the server
  server.begin();
  Serial.print("HTTP API server started on port ");
  Serial.println(SERVER_PORT);
}

void loop() {
  // Handle client requests
  server.handleClient();
}

// Function to handle GET requests to the "/settings/about" endpoint
void handleAbout() {
  // Create a JSON response with the firmware version
  String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";

  // Send the JSON response
  server.send(200, "application/json", jsonResponse);
}
