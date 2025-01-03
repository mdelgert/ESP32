#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <NimBLEDevice.h>
#include "MessagePrinter.h"
#include "FeatureManager.h"

class BluetoothHandler {
private:
    MessagePrinter &printer;
    FeatureManager &features;

public:
    BluetoothHandler(MessagePrinter &printer, FeatureManager &features)
        : printer(printer), features(features) {}

    void init() {
        if (ENABLE_BLUETOOTH) {
            NimBLEDevice::init("ESP32");
            printer.print("Bluetooth initialized");
        }
    }

    void update() {
        // Process Bluetooth events
    }
};

#endif
