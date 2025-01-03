#include "Arduino.h"
#include "FS.h"
#include "SD_MMC.h"

// Correct pin definitions for LILYGO T-Dongle-S3
int d0 = 14;   // SDMMC_D0
int d1 = 17;   // SDMMC_D1
int d2 = 21;   // SDMMC_D2
int d3 = 18;   // SDMMC_D3
int clk = 12;  // SDMMC_CLK
int cmd = 16;  // SDMMC_CMD

const char *testFilePath = "/testfile.txt";

void writeTestFile(int loopCounter) {
    //File file = SD_MMC.open(testFilePath, FILE_APPEND); // Append mode
    File file = SD_MMC.open(testFilePath, FILE_WRITE); // Overwrite mode
    if (!file) {
        Serial.println("Failed to open test file for writing.");
        return;
    }
    file.printf("Loop %d: Hello from LILYGO T-Dongle-S3!\n", loopCounter);
    Serial.printf("Appended new data to test file: Loop %d\n", loopCounter);
    file.close();
}

void readTestFile() {
    File file = SD_MMC.open(testFilePath, FILE_READ);
    if (!file) {
        Serial.println("Failed to open test file for reading.");
        return;
    }

    Serial.println("Reading test file:");
    while (file.available()) {
        Serial.write(file.read());
    }
    Serial.println();
    file.close();
}

void setup() {
    Serial.begin(115200);
    delay(1000); // Give time for Serial Monitor to connect

    // Set custom pins for SD card
    if (!SD_MMC.setPins(clk, cmd, d0, d1, d2, d3)) {
        Serial.println("Failed to set custom pins");
        while (true); // Stop execution
    }

    // Initialize SD card
    if (!SD_MMC.begin("/sdcard", true)) { // true enables auto-formatting
        Serial.println("Card Mount Failed and could not format");
        while (true); // Stop execution
    }

    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("No SD_MMC card attached");
        while (true); // Stop execution
    }

    Serial.print("SD_MMC Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %llu MB\n", cardSize);

    uint64_t totalBytes = SD_MMC.totalBytes() / (1024 * 1024);
    uint64_t usedBytes = SD_MMC.usedBytes() / (1024 * 1024);
    Serial.printf("Total space: %llu MB\n", totalBytes);
    Serial.printf("Used space: %llu MB\n", usedBytes);

    // Overwrite the test file with initial content
    File file = SD_MMC.open(testFilePath, FILE_WRITE);
    if (file) {
        file.println("Initial file content:");
        file.close();
        Serial.println("Test file initialized.");
    } else {
        Serial.println("Failed to initialize test file.");
    }
}

void loop() {
    static int loopCounter = 1;

    // Append new data to the test file
    writeTestFile(loopCounter);

    // Read and print the test file contents
    readTestFile();

    loopCounter++;
    delay(1000); // Wait 1 second before the next iteration
}
