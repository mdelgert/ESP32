# Arduino CLI - https://arduino.github.io/arduino-cli/0.36/installation/
```bash
# Add user to dial out for serial upload
sudo usermod -a -G dialout $USER

arduino-cli sketch new MyFirstSketch
# Board info and settings like CPU speed
arduino-cli board details --fqbn esp32:esp32:esp32s3
arduino-cli board details --fqbn m5stack:esp32:m5stack_atom

# List installed cores
arduino-cli core list

# Show installed libraries
arduino-cli lib list
```