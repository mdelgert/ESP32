arduino-cli compile --fqbn m5stack:esp32:m5stack_atom HomeAssistant1.ino
arduino-cli upload --port /dev/ttyUSB0 --fqbn m5stack:esp32:m5stack_atom HomeAssistant1.ino