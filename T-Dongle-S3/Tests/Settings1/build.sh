# No serial debugging
#arduino-cli compile --fqbn esp32:esp32:esp32s3 Settings1.ino

# Enable serial debugging
#arduino-cli compile --fqbn esp32:esp32:esp32s3 --build-property build.usbcdc.enabled=1 Settings1.ino
arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc Settings1.ino

arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 Settings1.ino