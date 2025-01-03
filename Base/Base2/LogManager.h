#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <Arduino.h>
#include "Config.h"
#include "TFTHandler.h"

class LogManager {
private:
    static TFTHandler tftHandler; // TFTHandler instance

public:
    static void init() {
        if (ENABLE_SERIAL) {
            Serial.begin(115200);
            //while (!Serial);
        }
        if (ENABLE_TFT) {
            tftHandler.init();
        }
    }

    static void log(const String &message) {
        if (ENABLE_SERIAL) {
            Serial.println(message);
        }
        if (ENABLE_TFT) {
            tftHandler.logMessage(message);
        }
    }

    static void clear() {
        if (ENABLE_TFT) {
            tftHandler.clear();
        }
    }
};

// Initialize static member
TFTHandler LogManager::tftHandler;

#endif // LOG_MANAGER_H
