#arduino-cli compile --fqbn m5stack:esp32:m5stack_atom Keyboard2.ino
#arduino-cli upload --port /dev/ttyUSB0 --fqbn m5stack:esp32:m5stack_atom Keyboard2.ino

arduino-cli compile --fqbn esp32:esp32:esp32s3:USBMode=default Keyboard2.ino
#arduino-cli compile --fqbn esp32:esp32:esp32s3 Keyboard2.ino
arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 Keyboard2.ino

#arduino-cli compile --fqbn rp2040:rp2040:adafruit_trinkeyrp2040qt Keyboard2.ino
#arduino-cli upload --port /dev/ttyACM0 --fqbn rp2040:rp2040:adafruit_trinkeyrp2040qt Keyboard2.ino



