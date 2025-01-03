#include "SDCardHandler.h"

// Static member variables
sdmmc_card_t *SDCardHandler::card = nullptr;
USBMSC SDCardHandler::MSC;

void SDCardHandler::init()
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

void SDCardHandler::update()
{
    // Add any periodic checks or operations if necessary
}

bool SDCardHandler::initializeSDCard()
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
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            Serial.println("[SDCardHandler] Failed to mount filesystem. Card may need formatting.");
        }
        else
        {
            Serial.printf("[SDCardHandler] Failed to initialize SD card (%s).\n", esp_err_to_name(ret));
        }
        return false;
    }

    Serial.println("[SDCardHandler] SD card initialized and mounted successfully.");
    return true;
}

void SDCardHandler::initializeUSBMSC()
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

int32_t SDCardHandler::onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize)
{
    uint32_t count = bufsize / card->csd.sector_size;
    esp_err_t err = sdmmc_read_sectors(card, (uint8_t *)buffer + offset, lba, count);
    return (err == ESP_OK) ? bufsize : -1;
}

int32_t SDCardHandler::onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize)
{
    uint32_t count = bufsize / card->csd.sector_size;
    esp_err_t err = sdmmc_write_sectors(card, buffer + offset, lba, count);
    return (err == ESP_OK) ? bufsize : -1;
}

bool SDCardHandler::onStartStop(uint8_t power_condition, bool start, bool load_eject)
{
    Serial.printf("[SDCardHandler] MSC Start/Stop: Power=%u, Start=%u, Eject=%u\n", power_condition, start, load_eject);
    return true;
}

void SDCardHandler::usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
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
