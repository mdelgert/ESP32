arduino-cli compile --fqbn m5stack:esp32:m5stack_atom
arduino-cli upload --port /dev/ttyUSB0 --fqbn m5stack:esp32:m5stack_atom
#arduino-cli compile -v --fqbn m5stack:esp32:m5stack_atom --output-dir ./build
#arduino-cli upload --port /dev/ttyUSB0 --fqbn m5stack:esp32:m5stack_atom --input-file ./build/BleJig.ino.bin
