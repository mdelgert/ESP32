#include <Arduino.h>  // Include Arduino core functions
#include "SerialHandler.h"
#include "DisplayHandler.h"
#include "ConfigSecure.h"

void initializeSerial()
{
    if (SERIAL_DEBUG) {
        Serial.begin(SERIAL_BAUD_RATE);  // Use the configurable baud rate
        while (!Serial) {
            // Wait for serial port to connect
        }
        //Serial.println("Serial debugging enabled.");
        displayMessage("Debug");
    }
}
