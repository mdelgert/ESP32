#include "Arduino.h"
#include "USB.h"
#include "USBMSC.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"
#include "pin_config.h"
#include "sdmmc_cmd.h"
#include <TFT_eSPI.h>  // Include the TFT library

USBMSC MSC;
TFT_eSPI tft = TFT_eSPI();  // Create an instance of TFT display
#define MOUNT_POINT "/sdcard"
sdmmc_card_t *card;

void sd_init(void) {
  esp_err_t ret;
  const char mount_point[] = MOUNT_POINT;

  // Configure SD card mount settings
  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024
  };

  // Initialize SDMMC host and slot configuration
  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

  // Set SDMMC pins from pin_config.h
  slot_config.clk = (gpio_num_t)SD_MMC_CLK_PIN;
  slot_config.cmd = (gpio_num_t)SD_MMC_CMD_PIN;
  slot_config.d0 = (gpio_num_t)SD_MMC_D0_PIN;
  slot_config.d1 = (gpio_num_t)SD_MMC_D1_PIN;
  slot_config.d2 = (gpio_num_t)SD_MMC_D2_PIN;
  slot_config.d3 = (gpio_num_t)SD_MMC_D3_PIN;

  // Configure GPIO pullups
  gpio_set_pull_mode((gpio_num_t)SD_MMC_CMD_PIN, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)SD_MMC_D0_PIN, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)SD_MMC_D1_PIN, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)SD_MMC_D2_PIN, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)SD_MMC_D3_PIN, GPIO_PULLUP_ONLY);

  // Mount the SD card
  ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);
  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      tft.println("Failed to mount filesystem.");
    } else {
      tft.printf("Failed to initialize card: %s\n", esp_err_to_name(ret));
    }
    return;
  }

  // Print card information to TFT display
  tft.println("Mounted:");
  tft.printf("Name: %s\n", card->cid.name);
  tft.printf("Size: %llu MB\n", (uint64_t)(card->csd.capacity) * card->csd.sector_size / (1024 * 1024));
}

static int32_t onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize) {
  uint32_t count = bufsize / card->csd.sector_size;
  sdmmc_write_sectors(card, buffer + offset, lba, count);
  return bufsize;
}

static int32_t onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize) {
  uint32_t count = bufsize / card->csd.sector_size;
  sdmmc_read_sectors(card, buffer + offset, lba, count);
  return bufsize;
}

void setup() {
  // Initialize TFT display
  tft.init();
  
  // Rotate the text by 90 degrees (portrait mode)
  tft.setRotation(3);  // Adjust the rotation; 2 is 90-degree clockwise
  
  tft.fillScreen(TFT_BLACK);  // Clear the screen with black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white with black background
  
  // Increase font size
  tft.setTextSize(2);  // Change the text size; adjust the multiplier as needed

  sd_init();  // Initialize SD card

  // Initialize USB Mass Storage
  MSC.vendorID("ESP32");       // max 8 chars
  MSC.productID("SD-Card");    // max 16 chars
  MSC.productRevision("1.0");  // max 4 chars
  MSC.onRead(onRead);          // Set read function
  MSC.onWrite(onWrite);        // Set write function
  MSC.mediaPresent(true);      // Indicate media is present
  MSC.begin(card->csd.capacity, card->csd.sector_size);  // Start MSC
}

void loop() {
  // Main loop (nothing needed here for now)
}
