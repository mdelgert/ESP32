#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "ESP32_AccessPoint";
const char* password = "12345678";

WebServer server(80);

void handlePost() {
  // Get the length of the POST data
  int contentLength = server.arg("plain").length();

  // Read the JSON data
  String json = server.arg("plain");

  // Print the received JSON data to the serial monitor
  Serial.println("Received JSON:");
  Serial.println(json);

  // Send a response to the client
  server.send(200, "application/json", "{\"status\":\"received\"}");
}

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as an access point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Define the POST route and attach the handler
  server.on("/settings", HTTP_POST, handlePost);

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
