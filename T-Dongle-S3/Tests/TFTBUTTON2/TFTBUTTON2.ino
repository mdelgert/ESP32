#include <TFT_eSPI.h>      // Include the graphics library
#include <OneButton.h>     // Include the OneButton library
#include "Config.h"

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

// Create an instance of the OneButton class
OneButton button(BTN_PIN, true);

// Function declarations
void handleClick();
void handleDoubleClick();
void handleLongPressStart();

void setup() {
  // Initialize the TFT display
  tft.init();
  tft.setRotation(3); // Set rotation to flip the screen
  
  tft.fillScreen(SCREEN_COLOR); // Clear the screen with defined screen color
  tft.setTextColor(TEXT_COLOR, TEXT_BACKGROUND); // Set text color and background
  tft.setTextSize(TEXT_SIZE); // Set text size
  
  // Position the cursor with defined values
  tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y);
  
  // Print "Hello World" on the screen initially
  tft.println("Start!");

  // Attach functions to button events
  button.attachClick(handleClick);
  button.attachDoubleClick(handleDoubleClick);
  button.attachLongPressStart(handleLongPressStart);
}

void loop() {
  // Continuously check the button status
  button.tick();
}

// Function to handle a single click
void handleClick() {
  tft.fillScreen(SCREEN_COLOR); // Clear the screen with defined screen color
  tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y);
  tft.println("Clicked!"); // Display "Clicked!" message
}

// Function to handle a double-click
void handleDoubleClick() {
  tft.fillScreen(SCREEN_COLOR); // Clear the screen with defined screen color
  tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y);
  tft.println("Double!"); // Display "Double Clicked!" message
}

// Function to handle a long press
void handleLongPressStart() {
  tft.fillScreen(SCREEN_COLOR); // Clear the screen with defined screen color
  tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y);
  tft.println("Long!"); // Display "Long Pressed!" message
}
