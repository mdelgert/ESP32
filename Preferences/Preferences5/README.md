Please provide sample sketch for esp32-s3 that uses libraries Preferences.h and SimpleCLI.h.

Provide the following commands.

help (returns complete help commands)
version (returns application version)
set/get WifiSSID WifiPass MqttBroker MqttPort MqttTopic MqttUser MqttPass Password1 through Password10
list (lists all passwords and settings)
erase (erase all stored settings)

Please dont provide any logic to connect to wifi also break this code down.

Please break the code down using the following pattern so I can reuse it. Please put Preferences and SimpleCli in its own handler and keep the main sketch as simple as possible.

#ifndef EXAMPLE_HANDLER_H
#define EXAMPLE_HANDLER_H

class ExampleHandler {
private:
    static void performExampleAction() {
        //Todo
    }

public:
    static void init() {
        // todo
    }
};

#endif // EXAMPLE_HANDLER_H