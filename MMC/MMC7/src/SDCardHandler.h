#ifndef SDCARDHANDLER_H
#define SDCARDHANDLER_H

#include "Arduino.h"
#include "USB.h"
#include "USBMSC.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include <FS.h>
#include <SD_MMC.h>

class SDCardHandler
{
public:
    // Initialize SD card and USB MSC
    static void init()
    {
        Serial.println("[SDCardHandler] Initializing...");
        if (!initializeSDCard())
        {
            Serial.println("[SDCardHandler] SD card initialization failed.");
            return;
        }
        initializeUSBMSC();
        USB.begin(); // Start USB
        Serial.println("[SDCardHandler] Initialization complete.");
    }

    // Optional periodic updates
    static void update()
    {
        // Add periodic tasks if necessary
    }

    // Write a string to the log file
    static bool writeToLogFile(const String &data)
    {
        return writeFile(LOG_FILE_PATH, data);
    }

    // Read the contents of the log file
    static String readLogFile()
    {
        return readFile(LOG_FILE_PATH);
    }

    // Write data to a specific file
    static bool writeFile(const char *path, const String &data)
    {
        File file = SD_MMC.open(path, FILE_WRITE);
        if (!file)
        {
            Serial.printf("[SDCardHandler] Failed to open file for writing: %s\n", path);
            return false;
        }
        file.print(data);
        file.close();
        Serial.printf("[SDCardHandler] Data written to file: %s\n", path);
        return true;
    }

    // Read data from a specific file
    static String readFile(const char *path)
    {
        File file = SD_MMC.open(path, FILE_READ);
        if (!file)
        {
            Serial.printf("[SDCardHandler] Failed to open file for reading: %s\n", path);
            return "";
        }
        String content;
        while (file.available())
        {
            content += char(file.read());
        }
        file.close();
        Serial.printf("[SDCardHandler] Data read from file: %s\n", path);
        return content;
    }

    // Delete a specific file
    static bool deleteFile(const char *path)
    {
        if (SD_MMC.remove(path))
        {
            Serial.printf("[SDCardHandler] File deleted: %s\n", path);
            return true;
        }
        Serial.printf("[SDCardHandler] Failed to delete file: %s\n", path);
        return false;
    }

private:
    static sdmmc_card_t *card;
    static USBMSC MSC;

    // SD Card Pin Definitions
    static constexpr int SD_MMC_D0_PIN = 14;
    static constexpr int SD_MMC_D1_PIN = 17;
    static constexpr int SD_MMC_D2_PIN = 21;
    static constexpr int SD_MMC_D3_PIN = 18;
    static constexpr int SD_MMC_CLK_PIN = 12;
    static constexpr int SD_MMC_CMD_PIN = 16;

    // Helper functions
    static bool initializeSDCard()
    {
        esp_vfs_fat_sdmmc_mount_config_t mount_config = {
            .format_if_mount_failed = false,
            .max_files = 5,
            .allocation_unit_size = 16 * 1024};

        sdmmc_host_t host = SDMMC_HOST_DEFAULT();
        host.slot = SDMMC_HOST_SLOT_1; // Specify SDMMC slot
        host.max_freq_khz = SDMMC_FREQ_DEFAULT;

        sdmmc_slot_config_t slot_config = {
            .clk = (gpio_num_t)SD_MMC_CLK_PIN,
            .cmd = (gpio_num_t)SD_MMC_CMD_PIN,
            .d0 = (gpio_num_t)SD_MMC_D0_PIN,
            .d1 = (gpio_num_t)SD_MMC_D1_PIN,
            .d2 = (gpio_num_t)SD_MMC_D2_PIN,
            .d3 = (gpio_num_t)SD_MMC_D3_PIN,
            .cd = SDMMC_SLOT_NO_CD,
            .wp = SDMMC_SLOT_NO_WP,
            .width = 4,
            .flags = SDMMC_SLOT_FLAG_INTERNAL_PULLUP};

        // Mount SD card
        esp_err_t ret = esp_vfs_fat_sdmmc_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);
        if (ret != ESP_OK)
        {
            Serial.printf("[SDCardHandler] Failed to initialize SD card (%s).\n", esp_err_to_name(ret));
            return false;
        }

        Serial.println("[SDCardHandler] SD card initialized and mounted successfully.");
        return true;
    }

    static void initializeUSBMSC()
    {
        MSC.vendorID("LILYGO");
        MSC.productID("T-Dongle-S3");
        MSC.productRevision("1.0");
        MSC.onStartStop(onStartStop);
        MSC.onRead(onRead);
        MSC.onWrite(onWrite);
        USB.onEvent(usbEventCallback);

        if (card)
        {
            MSC.mediaPresent(true);
            MSC.begin(card->csd.capacity, card->csd.sector_size);
            Serial.println("[SDCardHandler] USB Mass Storage initialized.");
        }
        else
        {
            Serial.println("[SDCardHandler] No SD card detected. USB MSC will not function.");
        }
    }

    // USB MSC Callbacks
    static int32_t onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize)
    {
        uint32_t count = bufsize / card->csd.sector_size;
        esp_err_t err = sdmmc_read_sectors(card, (uint8_t *)buffer + offset, lba, count);
        return (err == ESP_OK) ? bufsize : -1;
    }

    static int32_t onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize)
    {
        uint32_t count = bufsize / card->csd.sector_size;
        esp_err_t err = sdmmc_write_sectors(card, buffer + offset, lba, count);
        return (err == ESP_OK) ? bufsize : -1;
    }

    static bool onStartStop(uint8_t power_condition, bool start, bool load_eject)
    {
        Serial.printf("[SDCardHandler] MSC Start/Stop: Power=%u, Start=%u, Eject=%u\n", power_condition, start, load_eject);
        return true;
    }

    static void usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
    {
        if (event_base == ARDUINO_USB_EVENTS)
        {
            switch (event_id)
            {
            case ARDUINO_USB_STARTED_EVENT:
                Serial.println("[SDCardHandler] USB connected.");
                break;
            case ARDUINO_USB_STOPPED_EVENT:
                Serial.println("[SDCardHandler] USB disconnected.");
                break;
            case ARDUINO_USB_SUSPEND_EVENT:
                Serial.println("[SDCardHandler] USB suspended.");
                break;
            case ARDUINO_USB_RESUME_EVENT:
                Serial.println("[SDCardHandler] USB resumed.");
                break;
            default:
                break;
            }
        }
    }

    // File paths
    static constexpr const char *LOG_FILE_PATH = "/logfile.txt";
    static constexpr const char *MOUNT_POINT = "/sdcard";
};

// Static member definitions
sdmmc_card_t *SDCardHandler::card = nullptr;
USBMSC SDCardHandler::MSC;

#endif // SDCARDHANDLER_H
