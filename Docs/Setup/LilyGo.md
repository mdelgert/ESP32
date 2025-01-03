# Setup T-Dongle board - https://github.com/Xinyuan-LilyGO/T-Dongle-S3?spm=a2g0o.detail.1000023.11.49842ffcrnClM3
```bash
# See current boards installed
# arduino-cli board listall # does not list core boards
arduino-cli core list
# Search for a board
arduino-cli core search esp32
# You need to configure the Arduino CLI to use the custom package index URL. Run the following command.
arduino-cli config init
# This will creates file ~/.arduino15/arduino-cli.yaml can add to yaml file or via command
arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
# Update index
arduino-cli core update-index
# Install specific board version
#arduino-cli core install esp32:esp32@2.0.14
arduino-cli core install esp32:esp32@2.0.17
```

# Setup libraries
```bash
arduino-cli lib search NimBLE
#arduino-cli lib install "NimBLE-Arduino"
# Specify version
arduino-cli lib install "NimBLE-Arduino"@1.4.2
arduino-cli lib install "OneButton"@2.0.2
arduino-cli lib install "ArduinoWebsockets"@0.5.4
arduino-cli lib install "FastLED"@3.5.0
arduino-cli lib install "ArduinoWebsockets"@0.5.4
arduino-cli lib install "PubSubClient"@2.8.0
arduino-cli lib install "ArduinoJson"@7.1.0
arduino-cli lib install "LovyanGFX"@1.2.0

# Setup T-Dongle tft library (as of this time not wotking with core higher than esp32:esp32@2.0.14) switching to LovyanGFX.hpp
```bash
arduino-cli lib install "TFT_eSPI"@2.5.43
```

# Update User_Setup_Select.h
Comment out #include <User_Setup.h> 
Uncomment #include <User_Setups/Setup209_LilyGo_T_Dongle_S3.h> 

# Verfiy library install
```bash
arduino-cli lib list
```

# ############################# No longer needed see installation above #############################
# Setup T-Dongle tft library - https://github.com/Xinyuan-LilyGO/T-Dongle-S3/tree/main
```bash
# Orginal instructions says copy all libraries this appears to be all that is needed
cp -r ~/source/PassTxt/Arduino/T-Dongle-S3/lib/TFT_eSPI ~/Arduino/libraries/TFT_eSPI
```
# ############################# No longer needed see above #############################