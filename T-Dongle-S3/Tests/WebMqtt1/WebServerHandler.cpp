#include <WebServer.h>
#include "SecureConfig.h"
#include "WebServerHandler.h"  // Ensure this is included

// Create a web server object that listens for HTTP requests on the configurable port
WebServer server(SERVER_PORT);

void initWebServer() {
  // Define the REST API endpoint and associate it with a function
  server.on("/settings/about", HTTP_GET, handleAbout); // This should now correctly reference handleAbout

  // Start the server
  server.begin();
  //Serial.print("HTTP API server started on port ");
  //Serial.println(SERVER_PORT);
}

void handleWebServerClient() {
  // Handle client requests for the web server
  server.handleClient();
}

// Function to handle GET requests to the "/settings/about" endpoint
void handleAbout() {
  // Create a JSON response with the firmware version
  String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";

  // Send the JSON response
  server.send(200, "application/json", jsonResponse);
}
