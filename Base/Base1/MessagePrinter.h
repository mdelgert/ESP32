#ifndef MESSAGE_PRINTER_H
#define MESSAGE_PRINTER_H

#include <TFT_eSPI.h>
#include <Arduino.h>
#include "Config.h"

class MessagePrinter {
private:
    TFT_eSPI tft;
    bool tftEnabled;
    bool serialEnabled;

public:
    MessagePrinter() : tftEnabled(ENABLE_TFT), serialEnabled(ENABLE_SERIAL) {}

    void init() {
        if (serialEnabled) Serial.begin(115200);
        if (tftEnabled) {
            tft.init();
            tft.setRotation(1);
            tft.fillScreen(TFT_BLACK);
        }
    }

    void print(const String &message) {
        if (serialEnabled) Serial.println(message);
        if (tftEnabled) {
            tft.fillScreen(TFT_BLACK);
            tft.drawString(message, 10, 10);
        }
    }
};

#endif
