//GfxHandler.h

#ifndef GFX_HANDLER_H
#define GFX_HANDLER_H

#include <LovyanGFX.hpp>
#include "Config.h"

// Define the display configuration for LILYGO T-Dongle-S3
class LGFX_LiLyGo_TDongleS3 : public lgfx::LGFX_Device {
    lgfx::Panel_ST7735S _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_LiLyGo_TDongleS3() {
        // SPI bus configuration
        auto cfg = _bus_instance.config();
        cfg.spi_host = SPI3_HOST; // SPI3 for ESP32-S3
        cfg.spi_mode = 0;         // SPI mode 0
        cfg.freq_write = 27000000; // Write frequency
        cfg.freq_read = 16000000; // Read frequency
        cfg.spi_3wire = true;     // 3-wire SPI
        cfg.pin_sclk = TFT_SCL_PIN; // SCLK pin
        cfg.pin_mosi = TFT_SDA_PIN; // MOSI pin
        cfg.pin_dc = TFT_DC_PIN;   // DC pin
        cfg.pin_miso = -1;        // No MISO pin
        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);

        // Panel configuration
        auto panel_cfg = _panel_instance.config();
        panel_cfg.pin_cs = TFT_CS_PIN; // CS pin
        panel_cfg.pin_rst = TFT_RES_PIN; // RST pin
        panel_cfg.panel_width = 80;  // Display width
        panel_cfg.panel_height = 160; // Display height
        panel_cfg.offset_x = 26; // X offset
        panel_cfg.offset_y = 1;  // Y offset
        panel_cfg.invert = true; // Invert colors
        _panel_instance.config(panel_cfg);

        // Backlight configuration
        auto light_cfg = _light_instance.config();
        light_cfg.pin_bl = TFT_LEDA_PIN; // Backlight pin
        light_cfg.invert = true;  // Inverted brightness
        light_cfg.freq = 12000;   // PWM frequency
        light_cfg.pwm_channel = 7; // PWM channel
        _light_instance.config(light_cfg);
        _panel_instance.setLight(&_light_instance);

        setPanel(&_panel_instance); // Attach the panel
    }
};

// Define the handler for LovyanGFX
class GfxHandler {
private:
    static LGFX_LiLyGo_TDongleS3 tft; // Instance of the display class

public:
    GfxHandler() {}

    static void init() {
        if (!ENABLE_TFT) return;
        tft.init(); // Initialize the display
        tft.setBrightness(128); // Set the backlight brightness
        tft.setRotation(1); // Adjust rotation (modify as needed)
        tft.fillScreen(TFT_BLACK); // Clear the screen
        tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on black background
        tft.setTextSize(2); // Set the text size
    }

    static void logMessage(const String &message) {
        if (!ENABLE_TFT) return;

        tft.fillScreen(TFT_BLACK); // Clear the screen
        tft.setCursor(5, 5);       // Position the cursor
        tft.println(message);      // Display the message
    }
};

// Define the static member inline to avoid additional definitions elsewhere
LGFX_LiLyGo_TDongleS3 GfxHandler::tft;

#endif // GFX_HANDLER_H
