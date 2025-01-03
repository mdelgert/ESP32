#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <Arduino.h>
#include "LogManager.h"
#include "LEDHandler.h"

class ButtonHandler {
private:
    LogManager &logManager;
    LEDHandler &ledHandler;
    int buttonPin;
    bool lastState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;

    bool readButton() {
        return digitalRead(buttonPin) == HIGH;
    }

public:
    ButtonHandler(LogManager &logManager, LEDHandler &ledHandler, int pin, unsigned long debounceDelay = 50)
        : logManager(logManager), ledHandler(ledHandler), buttonPin(pin), lastState(false), 
          lastDebounceTime(0), debounceDelay(debounceDelay) {}

    void init() {
        pinMode(buttonPin, INPUT_PULLUP);
        logManager.log("Button initialized.");
    }

    void update() {
        bool currentState = readButton();
        if (currentState != lastState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (currentState != lastState && currentState == HIGH) {
                handlePress();
            }
        }

        lastState = currentState;
    }

    void handlePress() {
        ledHandler.toggle();
        logManager.log("Button pressed.");
    }
};

#endif
