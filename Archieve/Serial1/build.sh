# Enable serial debugging
arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc Serial1.ino
#arduino-cli compile --fqbn esp32:esp32:esp32s3 Serial1.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 Serial1.ino