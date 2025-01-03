The provided code appears to be a full application written for the **LILYGO T-Dongle-S3**. It uses **ESP-IDF** and **LovyanGFX** to control an ST7735S display, as well as several other components like an RGB LED, button, and SD card. Here’s a breakdown of how you can adapt or reuse the display-related parts of this code to test your display with **LovyanGFX**.

---

### **Simplified Display Example**

To focus only on testing the display with LovyanGFX, let’s strip the code down and simplify it for basic functionality. This example will:
- Initialize the display.
- Turn on the backlight.
- Display simple text.

#### **Minimal LovyanGFX Display Test Code**

```cpp
#include "LovyanGFX.hpp"

// Define the display configuration for LILYGO T-Dongle-S3
class LGFX_LiLyGo_TDongleS3 : public lgfx::LGFX_Device {
  lgfx::Panel_ST7735S _panel_instance;
  lgfx::Bus_SPI       _bus_instance;
  lgfx::Light_PWM     _light_instance;

public:
  LGFX_LiLyGo_TDongleS3(void) {
    // SPI bus configuration
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI3_HOST;              // SPI3 for ESP32-S3
    cfg.spi_mode = 0;                      // SPI mode 0
    cfg.freq_write = 27000000;             // Write frequency
    cfg.freq_read = 16000000;              // Read frequency
    cfg.spi_3wire = true;                  // 3-wire SPI
    cfg.pin_sclk = 5;                      // SCLK pin
    cfg.pin_mosi = 3;                      // MOSI pin
    cfg.pin_dc = 2;                        // DC pin
    cfg.pin_miso = -1;                     // No MISO pin
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    // Panel configuration
    auto panel_cfg = _panel_instance.config();
    panel_cfg.pin_cs = 4;                  // CS pin
    panel_cfg.pin_rst = 1;                 // RST pin
    panel_cfg.panel_width = 160;           // Display width
    panel_cfg.panel_height = 80;           // Display height
    panel_cfg.offset_x = 26;               // X offset
    panel_cfg.offset_y = 1;                // Y offset
    panel_cfg.invert = true;               // Invert colors
    _panel_instance.config(panel_cfg);

    // Backlight configuration
    auto light_cfg = _light_instance.config();
    light_cfg.pin_bl = 38;                 // Backlight pin
    light_cfg.invert = true;               // Inverted brightness
    light_cfg.freq = 12000;                // PWM frequency
    light_cfg.pwm_channel = 7;             // PWM channel
    _light_instance.config(light_cfg);
    _panel_instance.setLight(&_light_instance);

    setPanel(&_panel_instance);            // Attach the panel
  }
};

// Create an instance of the display
LGFX_LiLyGo_TDongleS3 lcd;

extern "C" void app_main(void) {
  // Initialize the display
  if (!lcd.init()) {
    printf("LCD initialization failed!\n");
    return;
  }

  // Set backlight brightness
  lcd.setBrightness(128); // 50% brightness

  // Clear screen and draw text
  lcd.fillScreen(0x0000); // Black background
  lcd.setTextColor(0xFFFF, 0x0000); // White text, black background
  lcd.setTextSize(1); // Default text size
  lcd.setCursor(10, 10); // Position cursor
  lcd.println("Hello, T-Dongle-S3!");

  while (true) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
```

---

### **Key Features in the Code**
1. **SPI and Panel Configuration:**
   - SPI pins (`MOSI`, `SCLK`, `DC`, `CS`, `RST`) are configured based on your product's pin definitions.
   - Display offsets (`offset_x`, `offset_y`) are adjusted for the ST7735S.

2. **Backlight Control:**
   - The backlight is connected to GPIO 38 and configured with PWM for brightness control.

3. **Text Rendering:**
   - Simple text is drawn using `lcd.println()`.

4. **LovyanGFX for Modern ESP-IDF:**
   - Works seamlessly with ESP-IDF and uses DMA for efficient rendering.

---

### **Expected Output**
- The display should show:
  ```
  Hello, T-Dongle-S3!
  ```
  in white text on a black background.

---

### **Troubleshooting**
1. **No Backlight:**
   - Ensure GPIO 38 controls the backlight and is connected properly.
   - If the backlight remains off, check if the `invert` configuration in the backlight settings is correct (`light_cfg.invert = true`).

2. **No Display Output:**
   - Double-check all pin connections.
   - Verify the display driver is an **ST7735S**.
   - Confirm the display works on older firmware (e.g., ESP-IDF 4.x) to rule out hardware issues.

3. **Debugging:**
   - Add debug output to verify initialization:
     ```cpp
     printf("Initializing LCD...\n");
     if (!lcd.init()) {
       printf("LCD initialization failed!\n");
     } else {
       printf("LCD initialized successfully!\n");
     }
     ```

---

### **Why Use This Code?**
- **LovyanGFX**: Actively maintained and optimized for ESP32.
- **Simplified Configuration**: Matches your hardware’s specific pin assignments.
- **ESP-IDF Compatible**: Works with modern ESP-IDF versions, including 5.x.

Let me know if you see output or encounter any issues!