#include "Arduino.h"
#include "USB.h"
#include "USBMSC.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

// SD Card Pin Definitions
#define SD_MMC_D0_PIN 14
#define SD_MMC_D1_PIN 17
#define SD_MMC_D2_PIN 21
#define SD_MMC_D3_PIN 18
#define SD_MMC_CLK_PIN 12
#define SD_MMC_CMD_PIN 16

#define MOUNT_POINT "/sdcard"

// USB Mass Storage and Serial Communication objects
USBMSC MSC;
USBCDC USBSerial;
#define HWSerial Serial0 // Debug Serial

// SD Card information structure
sdmmc_card_t *card;

// Function to initialize the SD card
void sd_init()
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

  // Mount the SD card
  esp_err_t ret = esp_vfs_fat_sdmmc_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);
  if (ret != ESP_OK)
  {
    if (ret == ESP_FAIL)
    {
      USBSerial.println("Failed to mount filesystem. Card may need formatting.");
    }
    else
    {
      USBSerial.printf("Failed to initialize the SD card (%s). Check connections.\n", esp_err_to_name(ret));
    }
    return;
  }

  USBSerial.println("SD card initialized and mounted successfully.");
}

// Callback for USB MSC read operations
static int32_t onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize)
{
  uint32_t count = bufsize / card->csd.sector_size;
  esp_err_t err = sdmmc_read_sectors(card, (uint8_t *)buffer + offset, lba, count);
  return (err == ESP_OK) ? bufsize : -1;
}

// Callback for USB MSC write operations
static int32_t onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize)
{
  uint32_t count = bufsize / card->csd.sector_size;
  esp_err_t err = sdmmc_write_sectors(card, buffer + offset, lba, count);
  return (err == ESP_OK) ? bufsize : -1;
}

// Callback for USB MSC start/stop operations
static bool onStartStop(uint8_t power_condition, bool start, bool load_eject)
{
  HWSerial.printf("MSC Start/Stop: Power=%u, Start=%u, Eject=%u\n", power_condition, start, load_eject);
  return true;
}

// USB event callback for debugging
static void usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
  if (event_base == ARDUINO_USB_EVENTS)
  {
    switch (event_id)
    {
    case ARDUINO_USB_STARTED_EVENT:
      HWSerial.println("USB connected.");
      break;
    case ARDUINO_USB_STOPPED_EVENT:
      HWSerial.println("USB disconnected.");
      break;
    case ARDUINO_USB_SUSPEND_EVENT:
      HWSerial.println("USB suspended.");
      break;
    case ARDUINO_USB_RESUME_EVENT:
      HWSerial.println("USB resumed.");
      break;
    default:
      break;
    }
  }
}

// Setup function
void setup()
{
  HWSerial.begin(115200); // Initialize debug Serial
  HWSerial.setDebugOutput(true);

  sd_init(); // Initialize SD card

  // Setup USB MSC
  USB.onEvent(usbEventCallback);
  MSC.vendorID("LILYGO");       // Max 8 chars
  MSC.productID("T-Dongle-S3"); // Max 16 chars
  MSC.productRevision("1.0");   // Max 4 chars
  MSC.onStartStop(onStartStop);
  MSC.onRead(onRead);
  MSC.onWrite(onWrite);

  // Check if SD card is mounted and initialize MSC
  if (card)
  {
    MSC.mediaPresent(true);
    MSC.begin(card->csd.capacity, card->csd.sector_size);
    USBSerial.println("USB Mass Storage initialized.");
  }
  else
  {
    USBSerial.println("No SD card detected. USB MSC will not function.");
  }

  USB.begin(); // Start USB
}

// Main loop function
void loop()
{
  //delay(1000); // Simple delay to keep the loop alive
}
