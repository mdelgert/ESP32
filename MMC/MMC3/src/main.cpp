#include "Arduino.h"
#include "FS.h"
#include "SD_MMC.h"
#include "USB.h"
#include "USBMSC.h"

// Correct pin definitions for LILYGO T-Dongle-S3
int d0 = 14;   // SDMMC_D0
int d1 = 17;   // SDMMC_D1
int d2 = 21;   // SDMMC_D2
int d3 = 18;   // SDMMC_D3
int clk = 12;  // SDMMC_CLK
int cmd = 16;  // SDMMC_CMD

USBMSC MSC; // USB Mass Storage Class
uint64_t cardSize = 0; // Card size in bytes
uint32_t sectorSize = 512; // Default sector size

void setup() {
    Serial.begin(115200);
    delay(1000); // Wait for Serial Monitor

    // Set custom pins for SD_MMC
    if (!SD_MMC.setPins(clk, cmd, d0, d1, d2, d3)) {
        Serial.println("Failed to set custom pins for SD_MMC");
        while (true);
    }

    // Initialize SD card
    if (!SD_MMC.begin("/sdcard", true)) { // true enables auto-formatting
        Serial.println("Failed to initialize SD card");
        while (true);
    }

    // Get SD card details
    cardSize = SD_MMC.cardSize(); // Total size in bytes
    if (cardSize == 0) {
        Serial.println("Failed to retrieve card size");
        while (true);
    }
    cardSize /= sectorSize; // Convert to sectors
    Serial.printf("SD_MMC Card Size: %llu sectors (%llu MB)\n", cardSize, cardSize * sectorSize / (1024 * 1024));

    // Initialize USB Mass Storage
    MSC.vendorID("LILYGO");       // 8 chars max
    MSC.productID("T-Dongle-S3"); // 16 chars max
    MSC.productRevision("1.0");   // 4 chars max

    MSC.onStartStop([](uint8_t powerCondition, bool start, bool loadEject) {
        Serial.printf("MSC StartStop: Power %u, Start %u, Eject %u\n", powerCondition, start, loadEject);
        return true;
    });

    MSC.onRead([](uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize) -> int32_t {
        File file = SD_MMC.open("/sdcard/disk.img", FILE_READ);
        if (!file) {
            Serial.printf("Failed to open file for reading at LBA %u\n", lba);
            return -1;
        }
        file.seek(lba * sectorSize + offset);
        file.read((uint8_t *)buffer, bufsize);
        file.close();
        return bufsize;
    });

    MSC.onWrite([](uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize) -> int32_t {
        File file = SD_MMC.open("/sdcard/disk.img", FILE_WRITE);
        if (!file) {
            Serial.printf("Failed to open file for writing at LBA %u\n", lba);
            return -1;
        }
        file.seek(lba * sectorSize + offset);
        file.write(buffer, bufsize);
        file.close();
        return bufsize;
    });

    MSC.begin(cardSize, sectorSize); // Initialize MSC with card size and sector size
    Serial.println("USB Mass Storage initialized!");
}

void loop() {
    delay(1000); // Keep the loop idle for MSC functionality
}
