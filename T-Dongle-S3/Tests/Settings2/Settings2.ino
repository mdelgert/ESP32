#include "ButtonHandler.h"
#include "DisplayHandler.h"
#include "WiFiHandler.h"
#include "WebServerHandler.h"
#include "SerialHandler.h"  // Include the new SerialHandler header
#include "ConfigSecure.h"

void setup()
{
    initializeSerial();  // Initialize serial communication
    initializeDisplay();
    initializeButton();
    initializeWiFi();
    initializeServer();
}

void loop()
{
    handleButton();       // Check button status
    handleWebServer();    // Handle client requests
}
