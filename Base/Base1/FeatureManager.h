#ifndef FEATURE_MANAGER_H
#define FEATURE_MANAGER_H

#include "WiFiManager.h"
#include "MessagePrinter.h"

class FeatureManager {
private:
    MessagePrinter &printer;
    WiFiManager wifiManager;

public:
    FeatureManager(MessagePrinter &printer)
        : printer(printer), wifiManager(printer) {}

    void init() {
        wifiManager.init();
        printer.print("FeatureManager initialized.");
    }

    void update() {
        // Update or manage other features
    }
};

#endif
