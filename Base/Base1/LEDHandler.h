#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include <Arduino.h>
#include "Config.h"
#include "LogManager.h"

class LEDHandler {
private:
    LogManager &logManager;
    int ledPin;
    bool state;

public:
    LEDHandler(LogManager &logManager, int pin = LED_PIN) 
        : logManager(logManager), ledPin(pin), state(false) {}

    void init() {
        pinMode(ledPin, OUTPUT);
        turnOff();
        logManager.log("LED initialized.");
    }

    void turnOn() {
        state = true;
        digitalWrite(ledPin, HIGH);
        logManager.log("LED turned ON.");
    }

    void turnOff() {
        state = false;
        digitalWrite(ledPin, LOW);
        logManager.log("LED turned OFF.");
    }

    void toggle() {
        state = !state;
        digitalWrite(ledPin, state ? HIGH : LOW);
        logManager.log(state ? "LED toggled ON." : "LED toggled OFF.");
    }

    bool isOn() const {
        return state;
    }
};

#endif
