https://www.reddit.com/r/esp32/comments/xvyi78/i_made_a_lillygo_tdisplay_s3_setup_guide_with/
I don't recommend using TFT_eSPI with this. I mean, you can, but it's less than ideal.

The S3 supports a new LCD subsystem that uses DMA to control i8080 parallel bus connected LCDs like the T-Display has.

The subsystem was clearly designed for LVGL (although I don't know if anyone at Espressif would actually come out and say that) and doesn't interface in such a way that TFT_eSPI or my graphics library, htcw_gfx, nor LoyvanGFX, can take advantage of.

The upshot is 30% or better performance using the native LCD subsystem w/ say LVGL vs using TFT_eSPI w/ LVGL (that's the most straightforward way to compare the performance of each). I expect TFT_eSPI to perform comparably with LoyvanGFX.

The stock firmware actually does use the S3's native LCD subsystem hardware.

I made an hardware monitor project that uses the S3 w/ LVGL using the LCD subsystem

https://github.com/codewitch-honey-crisis/EspMon_TDisplayS3

## Answer

The Reddit post you referenced highlights an important distinction: the **ESP32-S3** has a **new LCD subsystem** specifically designed for **i8080 parallel bus displays**, like the one used in the LilyGO T-Display S3. This subsystem supports **DMA** (Direct Memory Access), which improves performance by offloading the display updates from the CPU. Libraries like **TFT_eSPI** do not fully utilize this subsystem, which can lead to reduced performance and compatibility issues with newer ESP32 core versions.

Here's a breakdown of the approach mentioned in the article and how you can adapt to it:

---

### **1. Understanding the LCD Subsystem**
The ESP32-S3's native LCD subsystem is:
- **Hardware-accelerated**: Uses DMA to transfer display data efficiently.
- **Integrated with LVGL**: The **Light and Versatile Graphics Library (LVGL)** is a high-performance graphics library designed to work with the LCD subsystem.
- **Designed for Parallel Interfaces (i8080 bus)**: Optimized for i8080 displays rather than SPI-driven displays, although SPI can still be used with some tweaks.

---

### **2. Why TFT_eSPI May Struggle**
- **Lack of DMA Utilization**: TFT_eSPI directly communicates with the display using software-driven SPI or parallel protocols. This bypasses the LCD subsystem and cannot use its DMA features.
- **Limited Optimization for ESP32-S3 Hardware**: TFT_eSPI is a generic library, and while optimized for many ESP32 models, it doesn't leverage the ESP32-S3's unique hardware capabilities.

---

### **3. The Recommended Approach**
The recommendation is to use the **ESP32-S3 native LCD driver with LVGL** for optimal performance. Here’s why:
- LVGL integrates with the ESP32-S3's **LCD subsystem**, enabling DMA and hardware acceleration.
- It supports advanced features like anti-aliasing, caching, and custom fonts.
- Native support for the ESP-IDF (Espressif IoT Development Framework).

---

### **4. How to Use LVGL with the Native LCD Subsystem**
To use the LCD subsystem with LVGL, follow these steps:

#### **Step 1: Install ESP-IDF**
The LCD subsystem is supported in the **ESP-IDF**. Install the ESP-IDF by following the [official guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/).

#### **Step 2: Create an ESP-IDF Project**
- Use the **LVGL ESP-IDF examples** as a starting point.
- Clone the LVGL ESP-IDF repository:
  ```bash
  git clone https://github.com/lvgl/lvgl_esp32_drivers.git
  cd lvgl_esp32_drivers/examples/esp32_s3_parallel
  ```

#### **Step 3: Update Display Configuration**
- Modify the `sdkconfig` file or the configuration header to match your display's parameters (e.g., resolution, pin mappings).

For example, your pin mappings might look like this:
```c
#define CONFIG_LCD_PIN_DATA0 14
#define CONFIG_LCD_PIN_DATA1 17
#define CONFIG_LCD_PIN_DATA2 21
#define CONFIG_LCD_PIN_DATA3 18
#define CONFIG_LCD_PIN_DATA4 12
#define CONFIG_LCD_PIN_DATA5 16
#define CONFIG_LCD_PIN_CS    4
#define CONFIG_LCD_PIN_WR    1
#define CONFIG_LCD_PIN_DC    2
#define CONFIG_LCD_PIN_RST   38
```

#### **Step 4: Initialize LVGL**
In your project, initialize LVGL with the native ESP32-S3 LCD driver:
```c
#include "lvgl.h"
#include "lvgl_helpers.h"

void app_main() {
    lv_init();

    // Initialize display and touch drivers
    lvgl_driver_init();

    // Create a simple LVGL screen
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello, ESP32-S3!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    while (1) {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
```

#### **Step 5: Build and Flash**
- Use the ESP-IDF tools to build and flash the firmware:
  ```bash
  idf.py build
  idf.py flash
  ```

---

### **5. Benefits of This Approach**
1. **Performance**: You’ll achieve ~30% better performance by leveraging DMA and hardware acceleration.
2. **Compatibility**: The native ESP32-S3 LCD driver is actively maintained and optimized for the ESP-IDF.
3. **Advanced Graphics**: LVGL supports complex UI elements like buttons, sliders, animations, and charts.

---

### **6. Alternative Lightweight Option**
If LVGL feels too complex and you only need basic graphics:
- Use the **ESP-IDF with the native LCD driver** without LVGL. This allows you to directly send simple text and graphics commands to the display using the LCD subsystem.

---

### **Conclusion**
If you want to future-proof your code and utilize the ESP32-S3 hardware optimally:
- **Switch to ESP-IDF** and use the **native LCD driver** with or without LVGL.
- For more advanced graphics or a polished UI, integrate LVGL with your project.

If you'd like, I can help you set up a specific example in the ESP-IDF!