//https://docs.m5stack.com/en/unit/ENV%E2%85%A3%20Unit
//https://github.com/m5stack/M5Unit-ENV/blob/master/examples/Unit_ENVIV_M5Core/Unit_ENVIV_M5Core.ino

#include <M5Atom.h>
#include "M5UnitENV.h"

// Define constants for pin configuration
const int SDA_PIN = 26;
const int SCL_PIN = 32;
const uint32_t I2C_FREQUENCY = 400000U;

SHT4X sht4;
BMP280 bmp;

void initializeSensor(SHT4X& sensor, const char* sensorName) {
    if (!sensor.begin(&Wire, SHT40_I2C_ADDR_44, SDA_PIN, SCL_PIN, I2C_FREQUENCY)) {
        Serial.printf("Couldn't find %s\n", sensorName);
        while (1) delay(1);
    }
    sensor.setPrecision(SHT4X_HIGH_PRECISION);
    sensor.setHeater(SHT4X_NO_HEATER);
}

void initializeSensor(BMP280& sensor, const char* sensorName) {
    if (!sensor.begin(&Wire, BMP280_I2C_ADDR, SDA_PIN, SCL_PIN, I2C_FREQUENCY)) {
        Serial.printf("Couldn't find %s\n", sensorName);
        while (1) delay(1);
    }
    sensor.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                       BMP280::SAMPLING_X2,     /* Temp. oversampling */
                       BMP280::SAMPLING_X16,    /* Pressure oversampling */
                       BMP280::FILTER_X16,      /* Filtering. */
                       BMP280::STANDBY_MS_500); /* Standby time. */
}

void setup() {
    M5.begin(true, false, true); // Initialize M5 Atom-Matrix with Serial and LED support
    delay(50);
    M5.dis.drawpix(0, 0x00ff00);

    initializeSensor(sht4, "SHT4x");
    initializeSensor(bmp, "BMP280");
}

void printSHT4XData() {
    if (sht4.update()) {
        Serial.println("-----SHT4X-----");
        Serial.printf("Temperature: %.2f degrees C\n", sht4.cTemp);
        Serial.printf("Humidity: %.2f%% rH\n", sht4.humidity);
        Serial.println("-------------\r\n");
    }
}

void printBMP280Data() {
    if (bmp.update()) {
        Serial.println("-----BMP280-----");
        Serial.printf("Temperature: %.2f degrees C\n", bmp.cTemp);
        Serial.printf("Pressure: %.2f Pa\n", bmp.pressure);
        Serial.printf("Approx altitude: %.2f m\n", bmp.altitude);
        Serial.println("-------------\r\n");
    }
}

void loop() {
    printSHT4XData();
    printBMP280Data();
    delay(1000);
}
