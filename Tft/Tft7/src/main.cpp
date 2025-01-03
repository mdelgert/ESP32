//main.cpp

#include <Arduino.h>
#include "GfxHandler.h"

void setup() {
    Serial.begin(115200);
    GfxHandler::init();
    Serial.println("Setup complete!");
    GfxHandler::logMessage("Setup complete!");
}

void loop() {
    static int counter = 0;
    counter++;              
    Serial.print("Hello:" + String(counter));
    GfxHandler::logMessage("Hello:" + String(counter));
    delay(1000);
}
