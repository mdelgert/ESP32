//DisplayHandler.cpp

#include <TFT_eSPI.h>
#include "DisplayHandler.h"
#include "ConfigSecure.h"

TFT_eSPI tft = TFT_eSPI();

void initializeDisplay()
{
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(SCREEN_COLOR);
    tft.setTextColor(TEXT_COLOR, TEXT_BACKGROUND);
    tft.setTextSize(TEXT_SIZE);
    displayMessage("Start!");
}

void displayMessage(const char* message)
{
    tft.fillScreen(SCREEN_COLOR);
    tft.setCursor(TEXT_CURSOR_X, TEXT_CURSOR_Y);
    tft.println(message);

    if (SERIAL_DEBUG) {
        Serial.println(message);
    }
}
