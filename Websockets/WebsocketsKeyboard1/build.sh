arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc WebsocketsKeyboard1.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 WebsocketsKeyboard1.ino
