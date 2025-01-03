#include <Arduino.h>
#include "NonBlockingTimer.h"

NonBlockingTimer myTimer(1000); // 1-second timer

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    if (myTimer.isReady())
    {
        Serial.println("Non-blocking delay triggered!");
    }
}
