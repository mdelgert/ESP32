# Setup TrinkeyRP2040 - https://learn.adafruit.com/adafruit-trinkey-qt2040/arduino-ide-setup
```bash
# See current boards installed
arduino-cli core list
# You need to configure the Arduino CLI to use the custom package index URL. Run the following command.
arduino-cli config init
# Add board
arduino-cli config add board_manager.additional_urls https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
# Update index
arduino-cli core update-index
# Search for a board
arduino-cli core search RP2040
# Install specific board
arduino-cli core install rp2040:rp2040
```