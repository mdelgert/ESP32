# Board info and settings like CPU speed
#arduino-cli board details --fqbn esp32:esp32:esp32s3

#arduino-cli compile --fqbn esp32:esp32:esp32s3 ButtonKeyboard1.ino
#arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=default,USBMode=hwcdc ButtonKeyboard1.ino
#arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=default,USBMode=default ButtonKeyboard1.ino
arduino-cli compile --fqbn esp32:esp32:esp32s3:USBMode=default ButtonKeyboard1.ino

arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 ButtonKeyboard1.ino