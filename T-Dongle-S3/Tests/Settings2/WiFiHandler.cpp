#include <WiFi.h>
#include "WiFiHandler.h"
#include "DisplayHandler.h"
#include "ConfigSecure.h"

void initializeWiFi()
{
    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        displayMessage("Connecting");
    }

    String ipAddress = WiFi.localIP().toString();
    displayMessage(ipAddress.c_str());
}
