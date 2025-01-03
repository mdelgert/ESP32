#ifndef BLUETOOTH_SERVER_HANDLER_H
#define BLUETOOTH_SERVER_HANDLER_H

#include <NimBLEDevice.h>
#include "LEDHandler.h"
#include "LogManager.h"
#include "KeyboardMouseHandler.h"
#include "Config.h"

class BluetoothServerHandler : public NimBLECharacteristicCallbacks, public NimBLEServerCallbacks {
private:
    static NimBLEServer* server;           // Bluetooth server
    static NimBLECharacteristic* characteristic; // Bluetooth characteristic
    static bool initialized;

    // Callback for received data
    void onWrite(NimBLECharacteristic* characteristic) override {
        std::string receivedData = characteristic->getValue();
        //LogManager::log("Received: " + String(receivedData.c_str()));

        LogManager::log(receivedData.c_str());
        KeyboardMouseHandler::sendKeys(receivedData.c_str());

        // LED Feedback
        LEDHandler::setColor(CRGB::Green, 50);

        // Process the received message
        // if (receivedData == "turn_off") {
        //     LEDHandler::turnOff();
        // } else if (receivedData.starts_with("send:")) {
        //     std::string message = receivedData.substr(5); // Extract text after "send:"
        //     KeyboardMouseHandler::sendKeys(message.c_str());
        // } else {
        //     LogManager::log("Unrecognized command: " + String(receivedData.c_str()));
        // }

        // Reset LED
        delay(500);
        LEDHandler::turnOff();
    }

    void onRead(NimBLECharacteristic* characteristic) override {
        LogManager::log("Characteristic read request.");
    }

    // Callback for when a device connects
    void onConnect(NimBLEServer* server) override {
        LogManager::log("Device connected.");
        LEDHandler::setColor(CRGB::Blue, 50); // Turn LED blue on connection
    }

    // Callback for when a device disconnects
    void onDisconnect(NimBLEServer* server) override {
        LogManager::log("Device disconnected.");
        LEDHandler::turnOff(); // Turn off LED on disconnection
    }

public:
    // Initialize the Bluetooth server
    static void init() {
        if (!ENABLE_BLUETOOTH_SERVER) {
            LogManager::log("Bluetooth server is disabled (ENABLE_BLUETOOTH_SERVER is false).");
            return;
        }

        if (initialized) {
            LogManager::log("BluetoothServerHandler already initialized.");
            return;
        }

        LogManager::log("Initializing Bluetooth server...");
        NimBLEDevice::init(DEVICE_NAME);

        server = NimBLEDevice::createServer();
        server->setCallbacks(new BluetoothServerHandler());

        NimBLEService* service = server->createService(SERVICE_UUID);

        characteristic = service->createCharacteristic(
            CHARACTERISTIC_UUID,
            NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
        );

        characteristic->setCallbacks(new BluetoothServerHandler());

        service->start();
        NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
        advertising->addServiceUUID(SERVICE_UUID);
        advertising->setScanResponse(true);
        advertising->start();

        initialized = true;
        LogManager::log("Bluetooth server started and advertising.");
    }
};

// Static member definitions
NimBLEServer* BluetoothServerHandler::server = nullptr;
NimBLECharacteristic* BluetoothServerHandler::characteristic = nullptr;
bool BluetoothServerHandler::initialized = false;

#endif // BLUETOOTH_SERVER_HANDLER_H
