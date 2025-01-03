https://docs.m5stack.com/en/arduino/arduino_board
https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
Search for M5Stack, and click Install

https://docs.m5stack.com/en/arduino/arduino_library
Search box (such as M5CoreS3, M5Core2, M5Unified), and click Install.

arduino-cli compile --fqbn m5stack:esp32:m5stack_atom LEDSet.ino
arduino-cli upload --port /dev/ttyUSB0 --fqbn m5stack:esp32:m5stack_atom LEDSet.ino