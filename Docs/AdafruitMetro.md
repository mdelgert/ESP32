https://docs.platformio.org/en/latest/boards/espressif32/adafruit_metro_esp32s3.html
https://docs.platformio.org/en/latest/plus/debug-tools/cmsis-dap.html#debugging-tool-cmsis-dap
https://www.visualmicro.com/page/ESP32-Debugging.aspx
https://learn.adafruit.com/adafruit-metro-esp32-s2/usage-with-adafruit-io
https://adafruit.github.io/Adafruit_WebSerial_ESPTool/
https://medium.com/@cjus/advanced-microcontroller-debugging-using-the-esp-prog-a97532e38e39
https://learn.adafruit.com/adafruit-metro-esp32-s2/debugging-with-openocd
https://www.visualmicro.com/page/ESP32S3-JTAG-Debugging.aspx
https://community.platformio.org/t/how-to-use-jtag-built-in-debugger-of-the-esp32-s3-in-platformio/36042
https://dialedin.com.au/blog/esp32-jtag-debugging-esp-prog

[env:adafruit_metro_esp32s3]
platform = espressif32
board = adafruit_metro_esp32s3

; change microcontroller
board_build.mcu = esp32s3

; change MCU frequency
board_build.f_cpu = 240000000L