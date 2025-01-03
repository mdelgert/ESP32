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
    LGFX_LiLyGo_TDongleS3();
};

// Define the handler for LovyanGFX
class GfxHandler {
private:
    static LGFX_LiLyGo_TDongleS3 tft; // Instance of the display class

public:
    GfxHandler() {}

    static void init();
    static void logMessage(const String &message);
};

#endif // GFX_HANDLER_H
