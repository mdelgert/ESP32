/*
 * This code sets up a BLE (Bluetooth Low Energy) server using the NimBLE library.
 * It defines UUIDs for the service and characteristic.
 * It includes callback classes to handle BLE events:
 * - MyServerCallbacks: Handles device connection and disconnection events.
 * - MyCallbacks: Handles write events to the characteristic, printing received values to the Serial monitor.
 */
#include <NimBLEDevice.h>

NimBLECharacteristic* pCharacteristic;
bool deviceConnected = false;

// Replace these with your actual UUIDs
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"         // Example: "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"  // Example: "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) {
        deviceConnected = true;
        Serial.println("Device connected!");
    }

    void onDisconnect(NimBLEServer* pServer) {
        deviceConnected = false;
        Serial.println("Device disconnected!");
    }
};

class MyCallbacks : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print("Received: ");
            Serial.println(value.c_str());
        }
    }
};

void setup() {
    Serial.begin(115200);
    
    // Wait for serial port to connect
    while (!Serial) {
    }
    
    //while (!Serial) {
    //delay(10);
    //}
    
    Serial.println("Starting ESP32 BLE server...");
    
    NimBLEDevice::init("ESP32_S3");
    
    NimBLEServer* pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    NimBLEService* pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE
    );
    pCharacteristic->setCallbacks(new MyCallbacks());

    pService->start();
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();
    
    Serial.println("Waiting for a client to connect...");
}

void loop() {
    // No additional code needed in the loop
}
