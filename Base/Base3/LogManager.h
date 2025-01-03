#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include "Config.h"
#include "TFTHandler.h"

class LogManager {
private:
    static TFTHandler tftHandler; // TFTHandler instance

public:
    static void init() {
        if (ENABLE_SERIAL) {
            Serial.begin(115200);
            delay(100);
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
};

// Initialize static member
TFTHandler LogManager::tftHandler;

#endif // LOG_MANAGER_H
