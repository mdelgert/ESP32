#include <TFT_eSPI.h>      // Include the graphics library
#include <OneButton.h>     // Include the OneButton library

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

// Define the button pin
const int buttonPin = 0;

// Create an instance of the OneButton class
OneButton button(buttonPin, true);

// Function declarations
void handleClick();
void handleDoubleClick();
void handleLongPressStart();

void setup() {
  // Initialize the TFT display
  tft.init();
  tft.setRotation(3); // Set rotation to flip the screen
  
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color to white and background to black
  tft.setTextSize(2); // Set text size to 2x the default size
  
  // Position the cursor (may need adjusting based on rotation)
  tft.setCursor(20, 30);
  
  // Print "Hello World" on the screen initially
  tft.println("Hello World");

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
  tft.fillScreen(TFT_BLUE); // Change screen color to blue on click
  tft.setCursor(20, 30);
  tft.println("Clicked!"); // Display "Clicked!" message
}

// Function to handle a double-click
void handleDoubleClick() {
  tft.fillScreen(TFT_GREEN); // Change screen color to green on double-click
  tft.setCursor(20, 30);
  tft.println("Double Clicked!"); // Display "Double Clicked!" message
}

// Function to handle a long press
void handleLongPressStart() {
  tft.fillScreen(TFT_RED); // Change screen color to red on long press
  tft.setCursor(20, 30);
  tft.println("Long Pressed!"); // Display "Long Pressed!" message
}
