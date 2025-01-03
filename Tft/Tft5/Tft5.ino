//arduino-cli lib install "LovyanGFX"@1.2.0
#include <LovyanGFX.hpp>
#include "lock.h" // Include the generated header file

// Define the display configuration for LILYGO T-Dongle-S3
class LGFX_LiLyGo_TDongleS3 : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7735S _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_LiLyGo_TDongleS3(void)
    {
        // SPI bus configuration
        auto cfg = _bus_instance.config();
        cfg.spi_host = SPI3_HOST;  // SPI3 for ESP32-S3
        cfg.spi_mode = 0;          // SPI mode 0
        cfg.freq_write = 27000000; // Write frequency
        cfg.freq_read = 16000000;  // Read frequency
        cfg.spi_3wire = true;      // 3-wire SPI
        cfg.pin_sclk = 5;          // SCLK pin
        cfg.pin_mosi = 3;          // MOSI pin
        cfg.pin_dc = 2;            // DC pin
        cfg.pin_miso = -1;         // No MISO pin
        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);

        // Panel configuration
        auto panel_cfg = _panel_instance.config();
        panel_cfg.pin_cs = 4;         // CS pin
        panel_cfg.pin_rst = 1;        // RST pin
        panel_cfg.panel_width = 80;   // Display width
        panel_cfg.panel_height = 160; // Display height
        panel_cfg.offset_x = 26;      // X offset
        panel_cfg.offset_y = 1;       // Y offset
        panel_cfg.invert = true;      // Invert colors
        _panel_instance.config(panel_cfg);

        // Backlight configuration
        auto light_cfg = _light_instance.config();
        light_cfg.pin_bl = 38;     // Backlight pin
        light_cfg.invert = true;   // Inverted brightness
        light_cfg.freq = 12000;    // PWM frequency
        light_cfg.pwm_channel = 7; // PWM channel
        _light_instance.config(light_cfg);
        _panel_instance.setLight(&_light_instance);

        setPanel(&_panel_instance); // Attach the panel
    }
};

// Create an instance of the display
LGFX_LiLyGo_TDongleS3 lcd;

void drawImage(int x, int y, int width, int height, char *data)
{
    uint8_t pixel[3]; // RGB values
    uint16_t color;

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            HEADER_PIXEL(data, pixel); // Decode pixel
            // Convert RGB888 to RGB565
            color = lcd.color565(pixel[0], pixel[1], pixel[2]);
            lcd.drawPixel(x + i, y + j, color); // Draw pixel on screen
        }
    }
}

void drawImageWithTransparency(int x, int y, int width, int height, char *data, uint16_t bgColor) {
  uint8_t pixel[3]; // RGB values
  uint16_t color;

  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      HEADER_PIXEL(data, pixel); // Decode pixel
      // Check if the pixel is white (255, 255, 255)
      if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
        // Skip white pixels or draw the background color
        lcd.drawPixel(x + i, y + j, bgColor);
      } else {
        // Convert RGB888 to RGB565 and draw the pixel
        color = lcd.color565(pixel[0], pixel[1], pixel[2]);
        lcd.drawPixel(x + i, y + j, color);
      }
    }
  }
}

void setup()
{
    lcd.init();
    lcd.setBrightness(128);
    lcd.setRotation(1);
    lcd.fillScreen(TFT_BLACK);

    /*
    lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    lcd.setTextSize(2);
    lcd.setCursor(5, 5);
    lcd.println("TFT5");
    */
    
    //Transparency background color
    //uint16_t bgColor = lcd.color565(128, 128, 128); // Grey background
    //uint16_t bgColor = lcd.color565(0, 0, 0); // Black background
    //drawImageWithTransparency(10, 10, width, height, header_data, bgColor);
    //drawImage(10, 10, width, height, header_data);
    drawImage(15, 8, width, height, header_data);
}

void loop()
{
    // Nothing to do in the loop
}
