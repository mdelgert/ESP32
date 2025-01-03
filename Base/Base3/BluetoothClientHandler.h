//Not implemented yet
#ifndef BLUETOOTH_CLIENT_HANDLER_H
#define BLUETOOTH_CLIENT_HANDLER_H

#include <NimBLEDevice.h>
#include "LEDHandler.h"
#include "LogManager.h"
#include "KeyboardMouseHandler.h"
#include "Config.h"

class BluetoothClientHandler : public NimBLECharacteristicCallbacks {
private:
    static NimBLEClient* client;       // Bluetooth client
    static bool connected;             // Connection status
    static bool initialized;           // Initialization status
    static NimBLEAdvertisedDevice* device; // Pointer to advertised device

    // Callback for received data
    void onWrite(NimBLECharacteristic* characteristic) override {
        std::string receivedData = characteristic->getValue();
        LogManager::log("Received: " + String(receivedData.c_str()));

        // LED feedback
        LEDHandler::setColor(CRGB::Green, 50);

        // Process the received message
        if (receivedData == "turn_off") {
            LEDHandler::turnOff();
        } else if (receivedData.starts_with("send:")) {
            std::string message = receivedData.substr(5); // Extract text after "send:"
            KeyboardMouseHandler::sendKeys(message.c_str());
        } else {
            LogManager::log("Unrecognized command: " + String(receivedData.c_str()));
        }

        // Reset LED
        delay(500);
        LEDHandler::turnOff();
    }

    // Callback for connection status
    void onConnect(NimBLEClient* client) {
        connected = true;
        LogManager::log("Bluetooth client connected.");
        LEDHandler::setColor(CRGB::Blue, 50);
    }

    void onDisconnect(NimBLEClient* client) {
        connected = false;
        LogManager::log("Bluetooth client disconnected.");
        LEDHandler::turnOff();
    }

public:
    // Initialize Bluetooth client
    static void init() {
        if (!ENABLE_BLUETOOTH_CLIENT) {
            LogManager::log("Bluetooth client is disabled (ENABLE_BLUETOOTH_CLIENT is false).");
            return;
        }

        if (initialized) {
            LogManager::log("BluetoothClientHandler already initialized.");
            return;
        }

        LogManager::log("Initializing Bluetooth client...");
        NimBLEDevice::init("ESP32_Client");
        initialized = true;
    }

    // Start scanning for devices
    static void startScan() {
        if (!ENABLE_BLUETOOTH_CLIENT) {
            LogManager::log("Bluetooth client is disabled.");
            return;
        }

        LogManager::log("Starting BLE scan...");
        NimBLEDevice::getScan()->setAdvertisedDeviceCallbacks(new BluetoothClientHandler());
        NimBLEDevice::getScan()->start(10, [](NimBLEScanResults results) {
            LogManager::log("Scan complete. Devices found: " + String(results.getCount()));
        });
    }

    // Connect to the advertised device
    static void connectToDevice(NimBLEAdvertisedDevice* device) {
        if (connected) {
            LogManager::log("Already connected to a device.");
            return;
        }

        client = NimBLEDevice::createClient();
        client->setClientCallbacks(new BluetoothClientHandler());
        if (client->connect(device)) {
            LogManager::log("Connected to device: " + String(device->getName().c_str()));

            NimBLEService* service = client->getService("YOUR_SERVICE_UUID");
            if (service) {
                NimBLECharacteristic* characteristic = service->getCharacteristic("YOUR_CHARACTERISTIC_UUID");
                if (characteristic) {
                    characteristic->subscribe(true);
                    LogManager::log("Subscribed to characteristic.");
                } else {
                    LogManager::log("Characteristic not found.");
                }
            } else {
                LogManager::log("Service not found.");
            }
        } else {
            LogManager::log("Failed to connect to device.");
        }
    }
};

// Static members definition
NimBLEClient* BluetoothClientHandler::client = nullptr;
bool BluetoothClientHandler::connected = false;
bool BluetoothClientHandler::initialized = false;
NimBLEAdvertisedDevice* BluetoothClientHandler::device = nullptr;

#endif // BLUETOOTH_CLIENT_HANDLER_H
