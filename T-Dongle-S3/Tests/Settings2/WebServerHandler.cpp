//WebServerHandler.cpp

#include <WebServer.h>
#include "WebServerHandler.h"
#include "DisplayHandler.h"
#include "ConfigSecure.h"
#include "SettingsHandler.h"
#include "SettingsPageHTML.h"  // Include the HTML page

WebServer server(SERVER_PORT);

// Reboot endpoint handler
void handleRebootEndpoint() {
    displayMessage("Rebooting");
    String jsonResponse = "{\"action\": \"reboot\"}";
    server.send(200, "application/json", jsonResponse); // Send JSON response
    delay(1000); // Allow time for the response to be sent before reboot
    ESP.restart();
}

// Update settings endpoint handler
void handleUpdateSettingsEndpoint() {
    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        displayMessage(("Received settings: " + body).c_str());  // Convert to const char*
        saveSettings(body);  // Save the received JSON
        server.send(200, "application/json", "{\"status\": \"saved\"}");
    } else {
        server.send(400, "application/json", "{\"error\": \"Invalid request\"}");
    }
}

// Get settings endpoint handler
void handleGetSettingsEndpoint() {
    String savedSettings = getSettings();  // Retrieve the saved JSON
    server.send(200, "application/json", savedSettings);
}

// Serve the HTML settings page at "/"
void handleRoot() {
    server.send(200, "text/html", settingsPageHTML); // Send the HTML page
}

// Initialize the server and define routes
void initializeServer() {
    server.on("/", handleRoot);  // Serve the root HTML page
    server.on("/device/reboot", handleRebootEndpoint);  // Add reboot endpoint
    server.on("/settings/update", handleUpdateSettingsEndpoint);  // Add update settings endpoint
    server.on("/settings/get", handleGetSettingsEndpoint);  // Add get settings endpoint
    server.begin();
}

// Handle incoming web server requests
void handleWebServer() {
    server.handleClient();
}

void handleAboutEndpoint() {
    displayMessage("About!");
    String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";
    server.send(200, "application/json", jsonResponse);
}
