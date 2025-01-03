/*
 * This code connects to a WiFi network and displays the connection status and IP address on a TFT screen using the TFT_eSPI library.
 * It includes:
 * - Initialization of the TFT display.
 * - Connecting to a WiFi network.
 * - Displaying the connection status and IP address on the TFT screen and Serial Monitor.
 */
#include <WiFi.h>      // Include the WiFi library
#include <TFT_eSPI.h>  // Include the TFT display library
#include "ConfigSecure.h" // Include the configuration file for credentials

// Create a TFT display instance
TFT_eSPI tft = TFT_eSPI();

// Function to print messages to the TFT
void printToTFT(const char* message) {
  tft.fillScreen(TFT_BLACK);  // Clear the screen
  tft.setCursor(10, 10);      // Set cursor position
  tft.println(message);       // Print message on the TFT
  Serial.println(message);    // Also print to the Serial Monitor
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize the TFT display
  tft.init();
  tft.setRotation(3);           // Set rotation (adjust as needed)
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);           // Set text size
  tft.fillScreen(TFT_BLACK);    // Clear the screen
  printToTFT("Connecting...");

  // Connect to WiFi using credentials from ConfigSecure.h
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print success message and IP address to TFT and Serial
  printToTFT("Connected!");
  delay(2000); // Delay to show the "WiFi Connected!" message
  tft.fillScreen(TFT_BLACK);    // Clear the screen again
  tft.setCursor(10, 10);        // Reset cursor position
  tft.println("IP:");
  tft.println(WiFi.localIP().toString().c_str()); // Print IP address
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing to do in the loop for this example
}
