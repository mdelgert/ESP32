#include "Arduino.h"
#include "logo.h"
#include "TFT_eSPI.h" // https://github.com/Bodmer/TFT_eSPI
#include "Config.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  pinMode(TFT_LEDA_PIN, OUTPUT);
  // Initialise TFT
  tft.init();
  //tft.setRotation(1);
  tft.setRotation(3); // Set rotation to flip the screen
  tft.fillScreen(TFT_DARKGREY);
  digitalWrite(TFT_LEDA_PIN, 0);
  tft.setTextFont(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.pushImage(0, 0, 160, 80, (uint16_t *)gImage_logo);
}

void loop() {
}
