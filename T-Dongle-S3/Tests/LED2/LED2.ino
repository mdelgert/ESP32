#include "pin_config.h"
#include <FastLED.h> 

CRGB leds;

//Flash multicolor
void led_task(void *param) {
  while (1) {
    static uint8_t hue = 0;
    leds = CHSV(hue++, 0XFF, 100);
    FastLED.show();
    delay(50);
  }
}

void setup() {
  // put your setup code here, to run once:
  // BGR ordering is typical
  FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(&leds, 1);

  //leds = CRGB::Red;
  //leds = CRGB::Blue;
  //leds = CRGB::Green;
  //FastLED.show();
  //xTaskCreatePinnedToCore(led_task, "led_task", 1024, NULL, 1, NULL, 0);
}

void loop() {
  // Flash the LED
  leds = CRGB::Green;
  FastLED.show();
  delay(500);
  
  // Now turn the LED off, then pause
  leds = CRGB::Black;
  FastLED.show();
  delay(500);
}
