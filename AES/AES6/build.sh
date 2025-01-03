arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc AES6.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 AES6.ino
