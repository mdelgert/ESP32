#include <WebServer.h>
#include "WebServerHandler.h"
#include "ConfigSecure.h"

WebServer server(SERVER_PORT);

void initializeServer()
{
    server.on("/settings/about", handleAboutEndpoint);
    server.begin();
}

void handleWebServer()
{
    server.handleClient();
}

void handleAboutEndpoint()
{
    String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";
    server.send(200, "application/json", jsonResponse);
}
