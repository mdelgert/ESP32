#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#define FASTLED_INTERNAL  // Suppress FastLED warnings
#include <FastLED.h>
#include "Config.h"
#include "LogManager.h"

// Configuration for FastLED
#define NUM_LEDS 1 // Adjust based on your setup
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

class LEDHandler {
private:
    CRGB leds[NUM_LEDS];
    uint8_t brightness;

public:
    LEDHandler(uint8_t pin = LED_PIN, uint8_t initialBrightness = 128) 
        : brightness(initialBrightness) {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.clear();
        FastLED.show();
    }

    void init() {
        setBrightness(brightness);
        setColor(CRGB::Black); // Initialize with LEDs off
        LogManager::log("LEDHandler initialized with FastLED.");
    }

    void setColor(const CRGB &color) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = color;
        }
        FastLED.show();
        LogManager::log("LED color updated.");
    }

    void setBrightness(uint8_t newBrightness) {
        brightness = newBrightness;
        FastLED.setBrightness(brightness);
        FastLED.show();
        LogManager::log(String("LED brightness set to ") + brightness);
    }

    void turnOff() {
        setColor(CRGB::Black);
        LogManager::log("LEDs turned off.");
    }

    void turnOn(const CRGB &color = CRGB::White) {
        setColor(color);
        LogManager::log("LEDs turned on.");
    }
};

#endif // LED_HANDLER_H
