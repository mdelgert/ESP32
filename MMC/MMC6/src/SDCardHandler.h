#ifndef SDCARDHANDLER_H
#define SDCARDHANDLER_H

#include "Arduino.h"
#include "USB.h"
#include "USBMSC.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

class SDCardHandler
{
public:
    static void init();
    static void update(); // Optional if monitoring or periodic actions are needed

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
    static bool initializeSDCard();
    static void initializeUSBMSC();

    // USB MSC Callbacks
    static int32_t onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize);
    static int32_t onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize);
    static bool onStartStop(uint8_t power_condition, bool start, bool load_eject);
    static void usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
};

#endif
