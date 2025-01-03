#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <TFT_eSPI.h>
#include <Arduino.h>
#include "Config.h"

class LogManager {
private:
    TFT_eSPI tft;
    bool tftEnabled;
    bool serialEnabled;

public:
    LogManager() : tftEnabled(ENABLE_TFT), serialEnabled(ENABLE_SERIAL) {}

    void init() {
        if (serialEnabled) Serial.begin(115200);
        if (tftEnabled) {
            tft.init();
            tft.setRotation(1);
            tft.fillScreen(TFT_BLACK);
        }
    }

    void log(const String &message) {
        if (serialEnabled) Serial.println(message);
        if (tftEnabled) {
            tft.fillScreen(TFT_BLACK);
            tft.drawString(message, 10, 10);
        }
    }
};

#endif
