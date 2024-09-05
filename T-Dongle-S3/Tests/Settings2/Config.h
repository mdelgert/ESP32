//ConfigSecure.h

#pragma once

// Enable serial debug
#define SERIAL_DEBUG true
#define SERIAL_BAUD_RATE 115200  // Define the baud rate for serial communication

// Wifi settings
#define SSID "IOT1"             // Replace with your SSID
#define PASSWORD "PWD"     // Replace with your Wi-Fi password
#define SERVER_PORT 80               // Server port

//Device settings
#define DEVICE_NAME "atom1"
#define DEVICE_SETUP true
#define DEVICE_ADMIN "admin"
#define DEVICE_PASSWORD "12345678"

// Pin configuration for hardware components
#define BTN_PIN        0   // Button pin - used for input (single, double, long press)
#define LED_DI_PIN    40   // LED data input pin
#define LED_CI_PIN    39   // LED clock input pin

// SD MMC (MicroSD card) pin configuration
#define SD_MMC_D0_PIN  14  // SD MMC data line 0
#define SD_MMC_D1_PIN  17  // SD MMC data line 1
#define SD_MMC_D2_PIN  21  // SD MMC data line 2
#define SD_MMC_D3_PIN  18  // SD MMC data line 3
#define SD_MMC_CLK_PIN 12  // SD MMC clock line
#define SD_MMC_CMD_PIN 16  // SD MMC command line

// OneButton settings
#define LONG_PRESS        10000

// Firmware version
#define FIRMWARE_VERSION "1.0.0"

// Display settings for TFT screen
#define SCREEN_COLOR     TFT_BLACK  // Background color of the screen
#define TEXT_COLOR       TFT_WHITE  // Text color displayed on the screen
#define TEXT_BACKGROUND  TFT_BLACK  // Text background color
#define TEXT_SIZE        2          // Text size for display
#define TEXT_CURSOR_X    5         // Initial X position for text cursor
#define TEXT_CURSOR_Y    5         // Initial Y position for text cursor

// TFT display pin configuration
#define TFT_CS_PIN     4   // TFT chip select pin
#define TFT_SDA_PIN    3   // TFT serial data pin
#define TFT_SCL_PIN    5   // TFT serial clock pin
#define TFT_DC_PIN     2   // TFT data/command control pin
#define TFT_RES_PIN    1   // TFT reset pin
#define TFT_LEDA_PIN  38   // TFT backlight control pin