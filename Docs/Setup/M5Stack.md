# Setup m5Stack board - https://docs.m5stack.com/en/arduino/arduino_board
```bash
# See current boards installed
arduino-cli core list
# You need to configure the Arduino CLI to use the custom package index URL. Run the following command.
arduino-cli config init
# Add board
arduino-cli config add board_manager.additional_urls https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
# Update index
arduino-cli core update-index
# Search for a board
arduino-cli core search m5stack
# Install specific board
arduino-cli core install m5stack:esp32
```

# Setup m5Stack libraries - https://docs.m5stack.com/en/arduino/arduino_library
```bash
# Show installed
arduino-cli lib list
# Search
arduino-cli lib search M5Atom
# Install
arduino-cli lib install "M5Atom"
```