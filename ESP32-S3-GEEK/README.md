# CLI setup
```bash
arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli board listall esp32
```

# Compile from CLI (not working)
```bash
arduino-cli compile --fqbn esp32:esp32:esp32s3
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3
#arduino-cli compile -v --fqbn esp32:esp32:esp32s3--output-dir ./build
#arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3--input-file ./build/Test.ino.bin
```
# Serial
In Arduino IDE go to tools "USB CDC on Boot Enabled"
First time may require unplug from USB and plug back in to work

# Links
https://www.waveshare.com/wiki/ESP32-S3-GEEK#01-WIFI_AP_LCD
https://files.waveshare.com/wiki/ESP32-S3-GEEK/ESP32-S3-GEEK_Code.zip
https://mqtt.waveshare.cloud/en/wavesharecloud-wiki.html
https://waveshare.cloud/
https://www.reddit.com/r/esp32/comments/114j40i/help_serial_monitor_not_working_with_a_new_esp32/