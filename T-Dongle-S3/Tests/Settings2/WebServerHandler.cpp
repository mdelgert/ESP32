#include <WebServer.h>
#include "WebServerHandler.h"
#include "DisplayHandler.h"
#include "ConfigSecure.h"

WebServer server(SERVER_PORT);

void handleRebootEndpoint()
{
    displayMessage("Rebooting");
    String jsonResponse = "{\"action\": \"reboot\"}";
    server.send(200, "application/json", jsonResponse); // Send JSON response
    delay(1000); // Allow time for the response to be sent before reboot
    ESP.restart();
}

void initializeServer()
{
    server.on("/settings/about", handleAboutEndpoint);
    server.on("/device/reboot", handleRebootEndpoint); // Add reboot endpoint
    server.begin();
}

void handleWebServer()
{
    server.handleClient();
}

void handleAboutEndpoint()
{
    displayMessage("About!");
    String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";
    server.send(200, "application/json", jsonResponse);
}
