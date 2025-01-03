arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc BUTTON1.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 BUTTON1.ino