#arduino-cli compile --fqbn esp32:esp32:esp32s3 Keyboard1.ino
arduino-cli compile --fqbn esp32:esp32:esp32s3:USBMode=default Keyboard1.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 Keyboard1.ino

