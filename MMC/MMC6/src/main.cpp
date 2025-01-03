#include "Arduino.h"
#include "SDCardHandler.h"

// Static initialization will ensure SDCardHandler initializes itself
void setup()
{
    Serial.begin(115200);
    SDCardHandler::init(); // Explicit initialization
}

void loop()
{
    // Main loop remains empty
}
