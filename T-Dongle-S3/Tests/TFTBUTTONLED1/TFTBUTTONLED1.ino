#define FASTLED_INTERNAL //remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#include <FastLED.h> 
#include <TFT_eSPI.h>      // Include the graphics library
#include <OneButton.h>     // Include the OneButton library
#include "Config.h"

CRGB leds;
TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class

// Create an instance of the OneButton class
OneButton button(BTN_PIN, true);

// Function declarations
void handleClick();
void handleDoubleClick();
void handleLongPressStart();

//Flash multicolor
void led_task_inf(void *param) {
  while (1) {
    static uint8_t hue = 0;
    leds = CHSV(hue++, 0XFF, 100);
    FastLED.show();
    delay(50);
  }
}

// Flash multicolor
void led_task(void *param) {
  int duration = *((int*)param);  // Cast and dereference the parameter to get the duration in seconds
  unsigned long startTime = millis();  // Record the start time

  while (1) {
    unsigned long elapsedTime = millis() - startTime;  // Calculate elapsed time

    if (elapsedTime >= duration * 1000) {  // Check if the specified duration has passed
      // Now turn the LED off
      leds = CRGB::Black;
      FastLED.show();
      break;  // Exit the loop
    }

    static uint8_t hue = 0;
    leds = CHSV(hue++, 0xFF, 100);
    FastLED.show();
    delay(50);
  }

  vTaskDelete(NULL);  // Delete the task after completion
}

void setup() {

  // Flash the LED
  FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(&leds, 1);
  //leds = CRGB::Red;
  //leds = CRGB::Blue;
  //leds = CRGB::Green;
  leds = CRGB::White;
  FastLED.show();
  
  int durationInSeconds = 60;  // Set the duration to 10 seconds
  xTaskCreatePinnedToCore(led_task, "led_task", 1024, &durationInSeconds, 1, NULL, 0);

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
