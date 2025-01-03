/*
 * This code handles button interactions and displays corresponding messages on a TFT screen using the TFT_eSPI library.
 * It includes functions to handle different types of button interactions:
 * - handleClick: Handles a single click event.
 * - handleDoubleClick: Handles a double-click event.
 * - handleLongPressStart: Handles the start of a long press event.
 */
#include <TFT_eSPI.h>      // Include the graphics library
#include <OneButton.h>     // Include the OneButton library

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

// Define the button pin
const int buttonPin = 0;

// Create an instance of the OneButton class
OneButton button(buttonPin, true);

// Reusable function to display text on TFT
void tftPrintln(const char* text) {
  tft.fillScreen(TFT_BLACK);  // Clear the screen
  tft.setCursor(20, 30);      // Set cursor position
  tft.println(text);          // Display text
}

// Function declarations
void handleClick();
void handleDoubleClick();
void handleLongPressStart();

void setup() {
  // Initialize the TFT display
  tft.init();
  tft.setRotation(3); // Set rotation to flip the screen
  
  // Configure text properties
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color to white and background to black
  tft.setTextSize(2); // Set text size to 2x the default size
  
  // Initial message
  tftPrintln("Button!");

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
  tftPrintln("Click!");
}

// Function to handle a double-click
void handleDoubleClick() {
  tftPrintln("Double!");
}

// Function to handle a long press
void handleLongPressStart() {
  tftPrintln("Long!");
}
