#ifndef NON_BLOCKING_TIMER_H
#define NON_BLOCKING_TIMER_H

#include <Arduino.h>

class NonBlockingTimer {
private:
    unsigned long previousMillis;
    unsigned long interval;

public:
    NonBlockingTimer(unsigned long interval) : previousMillis(0), interval(interval) {}

    void setInterval(unsigned long newInterval) {
        interval = newInterval;
    }

    bool isReady() {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            return true;
        }
        return false;
    }

    void reset() {
        previousMillis = millis();
    }
};

#endif // NON_BLOCKING_TIMER_H
