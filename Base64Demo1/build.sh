arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc Base64Demo1.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 Base64Demo1.ino
