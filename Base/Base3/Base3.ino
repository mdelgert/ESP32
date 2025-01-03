#include "CoreIncludes.h"

void setup() {
    LogManager::init();
    LEDHandler::init();
    ButtonHandler::init();
    WiFiHandler::init();
    WebSocketClientHandler::init();
    KeyboardMouseHandler::init();
    MouseJigglerHandler::init();
    BluetoothServerHandler::init();
    LEDHandler::setColor(CRGB::White);
}

void loop() {
    ButtonHandler::update();
    WiFiHandler::maintain();
    WebSocketClientHandler::loop();
    MouseJigglerHandler::jiggle();
}
