#arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc Tft3.ino
arduino-cli compile --fqbn esp32:esp32:esp32s3 Tft3.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 Tft3.ino