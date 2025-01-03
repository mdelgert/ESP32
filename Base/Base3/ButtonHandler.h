#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <OneButton.h>
#include "Config.h"
#include "LogManager.h"
#include "LEDHandler.h"
#include "KeyboardMouseHandler.h"

class ButtonHandler {
private:
    static OneButton button;

    // Actions for button events
    static void handleSingleClick() {
        LogManager::log("Single click detected.");
        LEDHandler::setColor(CRGB::Green); // Set LED to green on single click
        KeyboardMouseHandler::sendKeys("Single Click Triggered\n"); // Send string as keyboard input
    }

    static void handleDoubleClick() {
        LogManager::log("Double click detected.");
        LEDHandler::setColor(CRGB::Red); // Set LED to red on double click
        KeyboardMouseHandler::sendKeys("Double Click Triggered\n"); // Send string as keyboard input
    }

    static void handleLongPress() {
        LogManager::log("Long press detected.");
        LEDHandler::turnOff(); // Turn off LED on long press
        KeyboardMouseHandler::sendKeys("Long Press Triggered\n"); // Send string as keyboard input
    }

public:
    // Initialize the button
    static void init() {
        button = OneButton(BUTTON_PIN, true); // Initialize button with pin and active low
        button.attachClick(handleSingleClick);
        button.attachDoubleClick(handleDoubleClick);
        button.attachLongPressStart(handleLongPress);
        LogManager::log("ButtonHandler initialized.");
    }

    // Update the button state (call in loop)
    static void update() {
        button.tick();
    }
};

// Static member definition
OneButton ButtonHandler::button = OneButton(BUTTON_PIN, true);

#endif // BUTTON_HANDLER_H
