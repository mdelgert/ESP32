//ButtonHandler.cpp

#include <OneButton.h>
#include "ButtonHandler.h"
#include "DisplayHandler.h"
#include "ConfigSecure.h"

OneButton button(BTN_PIN, true);

void initializeButton()
{
    button.attachClick(handleClick);
    button.attachDoubleClick(handleDoubleClick);
    button.attachLongPressStart(handleLongPressStart);
    button.attachDuringLongPress(handleVeryLongPress);
}

void handleButton()
{
    button.tick();  // Continuously check button status
}

void handleClick()
{
    displayMessage("Clicked!");
}

void handleDoubleClick()
{
    displayMessage("Double!");
}

void handleLongPressStart()
{
    displayMessage("Long!");
}

void handleVeryLongPress()
{
    static unsigned long lastMillis = 0;
    if (millis() - lastMillis >= LONG_PRESS) {
        displayMessage("VeryLong!");
        lastMillis = millis();
    }
}
