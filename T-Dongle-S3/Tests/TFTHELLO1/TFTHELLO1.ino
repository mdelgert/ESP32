#include <TFT_eSPI.h>  // Include the graphics library

TFT_eSPI tft = TFT_eSPI();  // Create an instance of the TFT_eSPI class

void setup() {
  tft.init();                // Initialize the display
  //tft.setRotation(1);        // Set rotation to landscape mode (1 for 160x80)
  tft.setRotation(3);        // Set rotation to flip the screen

  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color to white and background to black
  tft.setTextSize(2);        // Set text size to 2x the default size
  
  // Position the cursor (may need adjusting based on rotation)
  tft.setCursor(20, 30);
  
  // Print "Hello World" on the screen
  tft.println("Hello World");
}

void loop() {
  // Nothing to do here
}
