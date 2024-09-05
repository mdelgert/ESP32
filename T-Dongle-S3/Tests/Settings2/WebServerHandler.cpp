//WebServerHandler.cpp

#include <WebServer.h>
#include "WebServerHandler.h"
#include "DisplayHandler.h"
#include "ConfigSecure.h"
#include "SettingsHandler.h"  // Include the new settings handler

WebServer server(SERVER_PORT);

void handleRebootEndpoint() {
    displayMessage("Rebooting");
    String jsonResponse = "{\"action\": \"reboot\"}";
    server.send(200, "application/json", jsonResponse); // Send JSON response
    delay(1000); // Allow time for the response to be sent before reboot
    ESP.restart();
}

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

void handleGetSettingsEndpoint() {
    String savedSettings = getSettings();  // Retrieve the saved JSON
    server.send(200, "application/json", savedSettings);
}

void initializeServer() {
    server.on("/settings/about", handleAboutEndpoint);
    server.on("/device/reboot", handleRebootEndpoint);  // Add reboot endpoint
    server.on("/settings/update", handleUpdateSettingsEndpoint);  // Add update settings endpoint
    server.on("/settings/get", handleGetSettingsEndpoint);  // Add get settings endpoint
    server.begin();
}

void handleWebServer() {
    server.handleClient();
}

void handleAboutEndpoint() {
    displayMessage("About!");
    String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";
    server.send(200, "application/json", jsonResponse);
}
