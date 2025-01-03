#define FASTLED_INTERNAL
#include <FastLED.h>
#include <Arduino.h>

// Define LED pins for LILYGO T-Dongle-S3
#define LED_DI_PIN 40 // Data Input Pin
#define LED_CI_PIN 39 // Clock Input Pin

// Number of LEDs
#define NUM_LEDS 1

// Create an LED array
CRGB leds[NUM_LEDS];

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup complete!");

    // Initialize FastLED with APA102 LED configuration
    FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(leds, NUM_LEDS);

    // Optional: Set brightness to avoid overdriving LEDs
    FastLED.setBrightness(100);
}

void loop()
{
    Serial.println("Hello1");
    delay(1000);

    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(500);

    leds[0] = CRGB::Black;
    FastLED.show();
    delay(500);
}
