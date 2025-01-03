#include "Config.h"
#include "LogManager.h"

void setup() {
    LogManager::init();
    LogManager::log("Hello2");
}

void loop() {
    // static unsigned long lastLogTime = 0;
    // if (millis() - lastLogTime > 1000) {
    //     LogManager::log("Logging a message to TFT.");
    //     lastLogTime = millis();
    // }
}
