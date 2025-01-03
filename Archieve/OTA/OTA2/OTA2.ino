#include <WiFi.h>
#include <ArduinoOTA.h>
#include <TFT_eSPI.h> // Include the TFT display library
#include "ConfigSecure.h" // Include configuration file

// TFT display instance
TFT_eSPI tft = TFT_eSPI();

// Function to print messages to TFT and Serial Monitor
void printMsg(const char* message) {
    if (DEBUG_TFT) {
        tft.fillScreen(TFT_BLACK); // Clear the screen
        tft.setCursor(10, 10);     // Set cursor position
        tft.println(message);      // Print message to TFT
    }

    if (DEBUG_SERIAL) {
        Serial.println(message);   // Print message to Serial Monitor
    }
}

// Function to connect to WiFi
void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    printMsg("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printMsg("Connecting..."); // Display connecting status repeatedly
    }
    printMsg("WiFi Connected");

    // Display the IP address after connection
    String ipMessage = "IP Address: " + WiFi.localIP().toString();
    printMsg(ipMessage.c_str());
}

void setup() {
    if (DEBUG_SERIAL) Serial.begin(115200);

    if (DEBUG_TFT) {
        // Initialize TFT display
        tft.init();
        tft.setRotation(3); // Adjust rotation as needed
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.fillScreen(TFT_BLACK);
    }

    // Connect to WiFi
    connectToWiFi();

    // Initialize OTA
    ArduinoOTA.setHostname(HOST_NAME);
    //ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.setPassword(nullptr); // Disable OTA password

    // OTA Event Handlers
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "Sketch";
        } else { // U_SPIFFS or U_LittleFS
            type = "Filesystem";
        }
        printMsg(("Start updating: " + type).c_str());
    });

    ArduinoOTA.onEnd([]() {
        printMsg("OTA Update Complete");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        char progressMsg[50];
        sprintf(progressMsg, "Progress: %u%%", (progress / (total / 100)));
        printMsg(progressMsg);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        String errorMsg = "Error: ";
        if (error == OTA_AUTH_ERROR) errorMsg += "Auth Failed";
        else if (error == OTA_BEGIN_ERROR) errorMsg += "Begin Failed";
        else if (error == OTA_CONNECT_ERROR) errorMsg += "Connect Failed";
        else if (error == OTA_RECEIVE_ERROR) errorMsg += "Receive Failed";
        else if (error == OTA_END_ERROR) errorMsg += "End Failed";
        printMsg(errorMsg.c_str());
    });

    ArduinoOTA.begin();
    //printMsg("OTA Ready");
    printMsg("V1");
}

void loop() {
    ArduinoOTA.handle(); // Handle OTA events
}
