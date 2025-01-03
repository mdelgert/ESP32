#ifndef WEBSOCKET_HANDLER_H
#define WEBSOCKET_HANDLER_H

#include <ArduinoWebsockets.h>
#include "MessagePrinter.h"
#include "FeatureManager.h"

class WebSocketHandler {
private:
    MessagePrinter &printer;
    FeatureManager &features;
    websockets::WebsocketsClient client;

public:
    WebSocketHandler(MessagePrinter &printer, FeatureManager &features)
        : printer(printer), features(features) {}

    void init() {
        if (ENABLE_WEBSOCKETS) {
            client.onMessage([this](websockets::WebsocketsMessage message) {
                this->handleMessage(message.data());
            });
            printer.print("WebSocket initialized");
        }
    }

    void update() {
        if (ENABLE_WEBSOCKETS) client.poll();
    }

    void handleMessage(const String &message) {
        printer.print("Received: " + message);
        // Process JSON and trigger actions
    }
};

#endif
