#include "Config.h"
#include "MessagePrinter.h"
#include "FeatureManager.h"
#include "BluetoothHandler.h"
#include "WebSocketHandler.h"

// Globals
MessagePrinter messagePrinter;
FeatureManager featureManager(messagePrinter);
BluetoothHandler bluetoothHandler(messagePrinter, featureManager);
WebSocketHandler webSocketHandler(messagePrinter, featureManager);

void setup() {
    // Initialize Serial and TFT display
    messagePrinter.init();
    
    // Initialize Features
    featureManager.init();
    bluetoothHandler.init();
    webSocketHandler.init();
    messagePrinter.print("Setup complete");
}

void loop() {
    featureManager.update();
    bluetoothHandler.update();
    webSocketHandler.update();
}
