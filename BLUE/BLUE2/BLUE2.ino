/*
 * This code sets up a BLE (Bluetooth Low Energy) server using the NimBLE library and displays information on a TFT screen using the TFT_eSPI library.
 * It defines UUIDs for the service and characteristic.
 * It includes callback classes to handle BLE events:
 * - MyServerCallbacks: Handles device connection and disconnection events.
 * - MyCallbacks: Handles write events to the characteristic, printing received values to the Serial monitor.
 * The TFT screen is used to display text.
 */
#include <TFT_eSPI.h>  // Include the graphics library
#include <NimBLEDevice.h>

// Create an instance of the TFT_eSPI class
TFT_eSPI tft = TFT_eSPI();

NimBLECharacteristic* pCharacteristic;
bool deviceConnected = false;

// Replace these with your actual UUIDs
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Define text area dimensions
#define TEXT_AREA_X 20
#define TEXT_AREA_Y 30
#define TEXT_AREA_WIDTH 200
#define TEXT_AREA_HEIGHT 30

// BLE Server Callbacks
class MyServerCallbacks : public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) override {
        deviceConnected = true;
        Serial.println("Device connected!");
    }

    void onDisconnect(NimBLEServer* pServer) override {
        deviceConnected = false;
        Serial.println("Device disconnected!");
    }
};

// BLE Characteristic Callbacks
class MyCallbacks : public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic) override {
        std::string value = pCharacteristic->getValue();
        if (!value.empty()) {
            Serial.print("Received: ");
            Serial.println(value.c_str());

            // Clear the specific text area before displaying the new message
            tft.fillRect(TEXT_AREA_X, TEXT_AREA_Y, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, TFT_BLACK);
            tft.setCursor(TEXT_AREA_X, TEXT_AREA_Y);
            tft.println(value.c_str());
        }
    }
};

void setup() {
    // Initialize the TFT display
    tft.init();
    tft.setRotation(3);  // Adjust screen orientation
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(TEXT_AREA_X, TEXT_AREA_Y);
    tft.println("Begin:");

    // Initialize Serial communication
    /*
    Serial.begin(115200);

    while (!Serial) {
    }

    //while (!Serial) {
    //    delay(10);
    //}
    */

    tft.fillRect(TEXT_AREA_X, TEXT_AREA_Y, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, TFT_BLACK);
    tft.setCursor(TEXT_AREA_X, TEXT_AREA_Y);
    tft.println("Starting");
    Serial.println("Starting");

    // Initialize BLE
    NimBLEDevice::init("PassTxtBT");
    NimBLEServer* pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create BLE Service and Characteristic
    NimBLEService* pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE
    );
    pCharacteristic->setCallbacks(new MyCallbacks());

    // Start BLE service and advertising
    pService->start();
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    tft.fillRect(TEXT_AREA_X, TEXT_AREA_Y, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, TFT_BLACK);
    tft.setCursor(TEXT_AREA_X, TEXT_AREA_Y);
    tft.println("Waiting");
    Serial.println("Waiting");
}

void loop() {
    // No additional code needed in the loop
}
