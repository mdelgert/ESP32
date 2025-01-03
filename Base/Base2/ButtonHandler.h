#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <OneButton.h>
#include "Config.h"
#include "LogManager.h"
#include "LEDHandler.h"

class ButtonHandler {
private:
    OneButton button;
    LEDHandler &ledHandler;

    static ButtonHandler *instance;

    // Handle single-click action
    static void handleSingleClickStatic() {
        if (instance) instance->handleSingleClick();
    }

    static void handleDoubleClickStatic() {
        if (instance) instance->handleDoubleClick();
    }

    static void handleLongPressStatic() {
        if (instance) instance->handleLongPress();
    }

    void handleSingleClick() {
        LogManager::log("Button single click detected.");
        ledHandler.setColor(CRGB::Green); // Example: Change LED color to green
    }

    void handleDoubleClick() {
        LogManager::log("Button double click detected.");
        ledHandler.setColor(CRGB::Red); // Example: Change LED color to red
    }

    void handleLongPress() {
        LogManager::log("Button long press detected.");
        static bool ledState = false;
        ledState = !ledState;
        if (ledState) {
            ledHandler.turnOn(CRGB::Blue); // Example: Turn LED on
        } else {
            ledHandler.turnOff(); // Example: Turn LED off
        }
    }

public:
    ButtonHandler(uint8_t pin, LEDHandler &led) 
        : button(pin, true), ledHandler(led) {}

    void init() {
        instance = this; // Set the static instance
        button.attachClick(handleSingleClickStatic);
        button.attachDoubleClick(handleDoubleClickStatic);
        button.attachLongPressStart(handleLongPressStatic);
        LogManager::log("ButtonHandler initialized.");
    }

    void update() {
        button.tick();
    }
};

// Initialize static member
ButtonHandler *ButtonHandler::instance = nullptr;

#endif // BUTTON_HANDLER_H
