# Bluekeyboard library from https://files.waveshare.com/wiki/ESP32-S3-GEEK/ESP32-S3-GEEK_Code.zip

For TFT tests copied folder lib\TFT_eSPI to Documents\Arduino\libraries
Everything worked may not require more setup than that.
Select board esp32s3

# Setup CLI
```bash
arduino-cli config init
arduino-cli config set board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core update-index
arduino-cli core search esp32
arduino-cli core install esp32:esp32@2.0.11
```