#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WebServer.h>

// Create an instance of the web server on port 80
WebServer server(80);

// Function to handle POST requests
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

// Function to set up the web server routes
void setupWebServer() {
  // Define the POST route and attach the handler
  server.on("/settings", HTTP_POST, handlePost);

  // Start the server
  server.begin();
}

// Function to handle client requests
void handleWebServerClient() {
  server.handleClient();
}

#endif // WEBSERVERHANDLER_H
