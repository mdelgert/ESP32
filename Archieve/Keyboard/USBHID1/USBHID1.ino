/*
 * This code sets up USB HID (Human Interface Device) peripherals (keyboard and mouse) and displays information on a TFT screen using the TFT_eSPI library.
 * It defines a button and uses the OneButton library to handle button interactions.
 * The code includes:
 * - Initialization of USB HID keyboard and mouse.
 * - Initialization of the TFT display.
 * - Definition of screen and text properties.
 * - A reusable function for printing messages to the TFT screen and sending keystrokes via the USB HID keyboard.
 */
#include <TFT_eSPI.h>      // Include the graphics library
#include <OneButton.h>     // Include the OneButton library
#include "USB.h"
#include "USBHIDKeyboard.h"
#include "USBHIDMouse.h"

// USB peripherals
USBHIDKeyboard Keyboard;
USBHIDMouse Mouse;

// TFT display instance
TFT_eSPI tft = TFT_eSPI();

// Define the button pin
const int buttonPin = 0;

// OneButton instance
OneButton button(buttonPin, true);

// Screen and text properties
#define SCREEN_COLOR     TFT_BLACK
#define TEXT_COLOR       TFT_WHITE
#define TEXT_BACKGROUND  TFT_BLACK
#define TEXT_SIZE        2
#define TEXT_CURSOR_X    20
#define TEXT_CURSOR_Y    30

// Reusable function for printing messages to TFT and Keyboard
void printMsg(const char* message) {
  tft.fillScreen(SCREEN_COLOR);      // Clear the screen
  tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y); // Set cursor position
  tft.println(message);              // Display the message on TFT
  Keyboard.print(message);           // Send the message to the host via keyboard
}

// Function declarations
void handleClick();
void handleDoubleClick();
void handleLongPressStart();

void setup() {
  // Initialize the TFT display
  tft.init();
  tft.setRotation(3); // Rotate the screen for correct orientation
  
  // Configure text properties
  tft.setTextColor(TEXT_COLOR, TEXT_BACKGROUND);
  tft.setTextSize(TEXT_SIZE);

  // Display initial message
  //printMsg("Hello!");

  // Attach button event functions
  button.attachClick(handleClick);
  button.attachDoubleClick(handleDoubleClick);
  button.attachLongPressStart(handleLongPressStart);

  // Initialize USB peripherals
  USB.begin();
  delay(50);

  Keyboard.begin();
  Mouse.begin();
  delay(50);
}

void loop() {
  // Continuously check button events
  button.tick();
}

// Function to handle a single click
void handleClick() {
  printMsg("Clicked!"); // Display and send "Clicked!" message
}

// Function to handle a double-click
void handleDoubleClick() {
  printMsg("Double!"); // Display and send "Double!" message
}

// Function to handle a long press
void handleLongPressStart() {
  printMsg("Mouse!");  // Display and send "Mouse!" message
  Mouse.move(1000, 1000); // Move the mouse cursor
}
