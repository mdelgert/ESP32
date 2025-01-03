#ifndef MOUSE_JIGGLER_HANDLER_H
#define MOUSE_JIGGLER_HANDLER_H

#include "KeyboardMouseHandler.h"
#include "LogManager.h"
#include "LEDHandler.h"
#include "Config.h"

class MouseJigglerHandler {
private:
    static bool initialized;
    static unsigned long lastMoveTime;       // Time of the last jiggle in milliseconds
    static unsigned int jiggleInterval;     // Jiggle interval in seconds
    static int8_t moveDistance;             // Jiggle distance
    static unsigned long lastFlashTime;     // Time of the last LED flash
    static bool ledState;                   // Current LED state

public:
    static void init() {
        if (!ENABLE_MOUSE_JIGGLER) {
            LogManager::log("Mouse Jiggler is disabled (ENABLE_MOUSE_JIGGLER is false).");
            return;
        }

        if (!ENABLE_USB_HID) {
            LogManager::log("USB HID is disabled (ENABLE_USB_HID is false).");
            return;
        }

        if (initialized) {
            LogManager::log("MouseJigglerHandler already initialized.");
            return;
        }

        LogManager::log("Initializing Mouse Jiggler...");
        initialized = true;
        lastMoveTime = millis();
        lastFlashTime = millis();
        ledState = false;
        LogManager::log("Mouse Jiggler initialized with interval: " + String(jiggleInterval) + " seconds.");
    }

    static void jiggle() {
        if (!ENABLE_MOUSE_JIGGLER || !KeyboardMouseHandler::isInitialized()) {
            //LogManager::log("Mouse Jiggler cannot run.");
            return;
        }

        unsigned long currentTime = millis();
        unsigned long elapsedTime = (currentTime - lastMoveTime) / 1000; // Convert to seconds

        if (elapsedTime < jiggleInterval) {
            unsigned int timeRemaining = jiggleInterval - elapsedTime;
            LogManager::log("Mouse jiggler: " + String(timeRemaining) + " seconds remaining.");
            delay(500);
            return;
        }

        LogManager::log("Mouse jiggler activated.");
        KeyboardMouseHandler::getMouse().move(moveDistance, 0);
        delay(50);
        KeyboardMouseHandler::getMouse().move(-moveDistance, 0);
        lastMoveTime = currentTime; // Update the last jiggle time
    }

    static void setJiggleInterval(unsigned int intervalSeconds) {
        jiggleInterval = intervalSeconds; // Directly set in seconds
        LogManager::log("Mouse jiggler interval set to: " + String(jiggleInterval) + " seconds.");
    }

    static void setJiggleDistance(int8_t distance) {
        moveDistance = distance;
        LogManager::log("Mouse jiggler distance set to: " + String(moveDistance));
    }
};

// Static member definitions
bool MouseJigglerHandler::initialized = false;
unsigned long MouseJigglerHandler::lastMoveTime = 0;
unsigned int MouseJigglerHandler::jiggleInterval = 10; // Default to 5 seconds
unsigned long MouseJigglerHandler::lastFlashTime = 0;
int8_t MouseJigglerHandler::moveDistance = 2;
bool MouseJigglerHandler::ledState = false;

#endif // MOUSE_JIGGLER_HANDLER_H
