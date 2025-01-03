#define FASTLED_INTERNAL //remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#include "pin_config.h"
#include <FastLED.h> 

CRGB leds;

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
  // put your setup code here, to run once:
  // BGR ordering is typical
  FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(&leds, 1);

  //leds = CRGB::Red;
  //leds = CRGB::Blue;
  //leds = CRGB::Green;
  //FastLED.show();
  
  //xTaskCreatePinnedToCore(led_task_inf, "led_task_inf", 1024, NULL, 1, NULL, 0);

  int durationInSeconds = 60;  // Set the duration to 10 seconds
  xTaskCreatePinnedToCore(led_task, "led_task", 1024, &durationInSeconds, 1, NULL, 0);
}

void loop() {

  // // Flash the LED
  // leds = CRGB::Green;
  // FastLED.show();
  // delay(500);
  
  // // Now turn the LED off, then pause
  // leds = CRGB::Black;
  // FastLED.show();
  // delay(500);
}
