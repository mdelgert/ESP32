#ifndef TFT_HANDLER_H
#define TFT_HANDLER_H

#include <TFT_eSPI.h>
#include "Config.h"

class TFTHandler {
private:
    TFT_eSPI tft; // TFT display object

public:
    TFTHandler() : tft(TFT_eSPI()) {}

    void init() {
        if (!ENABLE_TFT) return;

        tft.init(); // Initialize the display using pre-configured settings
        tft.setRotation(3); // Set rotation (adjust as needed)
        tft.fillScreen(TFT_BLACK); // Clear the screen
        tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on black background
        tft.setTextSize(2); // Set text size
        logMessage("TFTHandler initialized.");
    }

    void logMessage(const String &message) {
        if (!ENABLE_TFT) return;

        tft.fillScreen(TFT_BLACK); // Clear the entire screen
        tft.setCursor(5, 5);       // Adjust for small screens
        tft.println(message);
    }
};

#endif // TFT_HANDLER_H
