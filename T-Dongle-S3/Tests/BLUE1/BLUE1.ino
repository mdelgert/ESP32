#include <NimBLEDevice.h>

// Define the UUID for the service and characteristic
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-abcdef987654"

// Device ID or name to advertise
#define DEVICE_NAME "MyBlue1"

// Create a BLE server
NimBLEServer* pServer = nullptr;
NimBLECharacteristic* pCharacteristic = nullptr;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    // Initialize the NimBLE device
    NimBLEDevice::init(DEVICE_NAME);
    pServer = NimBLEDevice::createServer();

    // Create a service
    NimBLEService* pService = pServer->createService(SERVICE_UUID);

    // Create a characteristic within the service
    pCharacteristic = pService->createCharacteristic(
                         CHARACTERISTIC_UUID,
                         NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
                       );

    // Start the service
    pService->start();

    // Start advertising the service
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->start();

    Serial.println("Waiting for a client connection...");
}

void loop() {
    // Put any main code here that you want to run continuously
}
