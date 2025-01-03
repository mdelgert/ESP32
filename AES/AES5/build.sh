arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc AES5.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 AES5.ino
