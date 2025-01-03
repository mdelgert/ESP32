//Test - https://github.com/espressif/arduino-esp32
//arduino-cli core install esp32:esp32@2.0.14 //Works
//arduino-cli core install esp32:esp32@2.0.15 //Works
//arduino-cli core install esp32:esp32@2.0.16 //Works
//arduino-cli core install esp32:esp32@2.0.17 //Works

#define FASTLED_INTERNAL
#include <FastLED.h>

// Define LED pins for LILYGO T-Dongle-S3
#define LED_DI_PIN 40  // Data Input Pin
#define LED_CI_PIN 39  // Clock Input Pin

// Number of LEDs
#define NUM_LEDS 1

// Create an LED array
CRGB leds[NUM_LEDS];

void setup() {
  // Initialize FastLED with APA102 LED configuration
  FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(leds, NUM_LEDS);

  // Optional: Set brightness to avoid overdriving LEDs
  FastLED.setBrightness(50);
}

void loop() {
  // Flash the LED with green and blue colors alternately
  leds[0] = CRGB::Purple;  // Set LED to green
  FastLED.show();         // Display the color
  delay(500);             // Wait 500ms

  leds[0] = CRGB::White;   // Set LED to blue
  FastLED.show();         // Display the color
  delay(500);             // Wait 500ms
}
