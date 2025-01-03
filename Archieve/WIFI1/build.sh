arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc WIFI1.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 WIFI1.ino
