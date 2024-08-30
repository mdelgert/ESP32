#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WebServer.h>
#include <Preferences.h>

// Create an instance of the web server on port 80
WebServer server(80);

// Preferences object to handle NVS (non-volatile storage)
Preferences preferences;

// Function to handle POST requests and save JSON data
void handlePost() {
  // Get the JSON data from the POST request
  String json = server.arg("plain");

  // Print the received JSON data to the serial monitor
  Serial.println("Received JSON:");
  Serial.println(json);

  // Save the JSON data to preferences
  preferences.begin("settings", false);
  preferences.putString("json_data", json);
  preferences.end();

  // Send a response to the client
  server.send(200, "application/json", "{\"status\":\"received\"}");
}

// Function to handle GET requests and return the saved JSON data
void handleGet() {
  // Retrieve the saved JSON data
  preferences.begin("settings", false);
  String storedJson = preferences.getString("json_data", "");
  preferences.end();

  // Check if JSON data is available
  if (storedJson.length() > 0) {
    server.send(200, "application/json", storedJson);
  } else {
    server.send(404, "application/json", "{\"error\":\"No settings found\"}");
  }
}

// Function to set up the web server routes and print stored settings
void setupWebServer() {
  // Initialize the Preferences library
  preferences.begin("settings", false);

  // Retrieve and print stored JSON settings if available
  String storedJson = preferences.getString("json_data", "");
  if (storedJson.length() > 0) {
    Serial.println("Stored settings:");
    Serial.println(storedJson);
  } else {
    Serial.println("No stored settings found.");
  }

  preferences.end();

  // Define the POST route and attach the handler
  server.on("/settings", HTTP_POST, handlePost);

  // Define the GET route to return the stored JSON data
  server.on("/settings", HTTP_GET, handleGet);

  // Start the server
  server.begin();
}

// Function to handle client requests
void handleWebServerClient() {
  server.handleClient();
}

#endif // WEBSERVERHANDLER_H
