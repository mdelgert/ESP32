arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc AesClean2.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 AesClean2.ino
