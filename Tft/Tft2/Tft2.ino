//Test - https://github.com/espressif/arduino-esp32
//arduino-cli core install esp32:esp32@2.0.14 //Works
//arduino-cli core install esp32:esp32@2.0.15 //not working
//arduino-cli core install esp32:esp32@2.0.16 //not working
//arduino-cli core install esp32:esp32@2.0.17 //not working

#include <TFT_eSPI.h> // Include the graphics library

TFT_eSPI tft = TFT_eSPI(); // Create an instance of TFT_eSPI

void setup() {
  // Initialize the display
  tft.init();
  tft.setRotation(3);  // Set screen rotation (0-3)
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color

  // Set text color, font size, and position
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on black background
  tft.setTextDatum(MC_DATUM); // Center text datum
  tft.setTextSize(3); // Text size multiplier

  // Display the "Hello" message
  tft.drawString("Hello", tft.width() / 2, tft.height() / 2);
}

void loop() {
  // Nothing to do in the loop
}
