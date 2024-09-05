//Settings.ino

#include <WiFi.h>
#include <WebServer.h>
#include <TFT_eSPI.h>
#include <OneButton.h>
#include "ConfigSecure.h"

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class
OneButton button(BTN_PIN, true); // Create an instance of the OneButton class

WebServer server(SERVER_PORT); // Create an instance of the WebServer class using the port from ConfigSecure.h

// Function declarations
void handleClick();
void handleDoubleClick();
void handleLongPressStart();
void displayMessage(const char* message);
void handleAboutEndpoint();

void setup()
{
    // Initialize serial communication if debugging is enabled
    if (SERIAL_DEBUG) {
        Serial.begin(SERIAL_BAUD_RATE);  // Use the configurable baud rate
        while (!Serial) {
            // Wait for serial port to connect
        }
        Serial.println("Serial debugging enabled.");
    }

    // Initialize the TFT display
    tft.init();
    tft.setRotation(3); // Set rotation to flip the screen
    tft.fillScreen(SCREEN_COLOR);                  // Clear the screen with defined screen color
    tft.setTextColor(TEXT_COLOR, TEXT_BACKGROUND); // Set text color and background
    tft.setTextSize(TEXT_SIZE);                    // Set text size

    // Print "Start!" on the screen initially
    displayMessage("Start!");

    // Attach functions to button events
    button.attachClick(handleClick);
    button.attachDoubleClick(handleDoubleClick);
    button.attachLongPressStart(handleLongPressStart);
    button.attachDuringLongPress(handleVeryLongPress);

    // Connect to Wi-Fi using credentials from ConfigSecure.h
    WiFi.begin(SSID, PASSWORD);

    // Wait until connected to Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        displayMessage("Connecting");
    }

    // Print the IP address to the TFT screen once connected
    String ipAddress = WiFi.localIP().toString();
    displayMessage(ipAddress.c_str());

    // Setup the web server
    server.on("/settings/about", handleAboutEndpoint); // Define endpoint
    server.begin(); // Start the server
}

void loop()
{
    // Continuously check the button status
    button.tick();

    // Handle client requests
    server.handleClient();
}

// Function to handle a single click
void handleClick()
{
    displayMessage("Clicked!");
}

// Function to handle a double-click
void handleDoubleClick()
{
    displayMessage("Double!");
}

// Function to handle a long press
void handleLongPressStart()
{
    displayMessage("Long!");
}

// Function to handle a very long press
void handleVeryLongPress()
{
    static unsigned long lastMillis = 0;
    if (millis() - lastMillis >= LONG_PRESS) {  // Check if LONG_PRESS seconds have passed
        displayMessage("Long Press!");
        lastMillis = millis();  // Reset timer
    }
}

// Centralized function to display a message on the TFT screen
void displayMessage(const char* message)
{
    tft.fillScreen(SCREEN_COLOR); // Clear the screen with defined screen color
    tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y);  // Set cursor position
    tft.println(message);  // Print the message to the screen

    // Optionally print the message to the serial monitor if debugging is enabled
    if (SERIAL_DEBUG) {
        Serial.println(message);
    }
}

// Function to handle the /settings/about endpoint
void handleAboutEndpoint()
{
    // Return a JSON response with the firmware version
    String jsonResponse = "{\"firmware_version\": \"" + String(FIRMWARE_VERSION) + "\"}";
    server.send(200, "application/json", jsonResponse);
}