#include "PreferencesHandler.h"
#include "CLIHandler.h"

void setup()
{
    Serial.begin(115200);
    PreferencesHandler::getInstance().init();  // Initialize Preferences globally
    CLIHandler::getInstance().init();          // Initialize CLI
}

void loop()
{
    CLIHandler::getInstance().update();
}
