#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLEHIDDevice.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-5678-1234-5678-abcdef123456"

class MyCallbacks : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Received: ");
        Serial.println(value.c_str());
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    //BLESecurity *pSecurity = new BLESecurity();
    //pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

    // Initialize the NimBLE device
    NimBLEDevice::init("BLUE6");

    // Create the BLE server
    NimBLEServer *pServer = NimBLEDevice::createServer();

    // Create a BLE service
    NimBLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE characteristic
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                             CHARACTERISTIC_UUID,
                                             NIMBLE_PROPERTY::READ |
                                             NIMBLE_PROPERTY::WRITE
                                           );

    // Set the callback for receiving data
    pCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setAppearance(HID_KEYBOARD);
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->start();

    Serial.println("Waiting for a client connection...");
}

void loop() {
    // Nothing to do here, everything is handled in the background by the callbacks
}
