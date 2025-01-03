#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#define FASTLED_INTERNAL
#include <FastLED.h>
#include "Config.h"

#define NUM_LEDS 1
#define LED_TYPE APA102
#define COLOR_ORDER BGR

class LEDHandler {
private:
    static CRGB leds[NUM_LEDS]; // Static array for LED data

    // Static task for infinite LED animation
    static void ledTaskInf(void *param) {
        while (1) {
            static uint8_t hue = 0;
            leds[0] = CHSV(hue++, 0xFF, 100); // Default brightness for animation
            FastLED.show();
            delay(50);
        }
    }

public:
    // Initialize the LEDHandler (static)
    static void init() {
        FastLED.addLeds<LED_TYPE, LED_DI_PIN, LED_CI_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.clear();
        FastLED.show();
    }

    // Set LED color with optional brightness (static)
    static void setColor(const CRGB &color, uint8_t brightness = 10) {
        FastLED.setBrightness(brightness); // Set the brightness
        leds[0] = color;
        FastLED.show();
    }

    // Turn off LEDs (static)
    static void turnOff() {
        setColor(CRGB::Black, 0);
    }

    // Start an infinite animation task (static)
    static void startInfiniteTask() {
        xTaskCreatePinnedToCore(ledTaskInf, "led_task_inf", 1024, NULL, 1, NULL, 0);
    }
};

// Define static member
CRGB LEDHandler::leds[NUM_LEDS];

#endif // LED_HANDLER_H
