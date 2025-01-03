---
# Arduino CLI Commands Cheatsheet

```bash
# List installed cores
arduino-cli core list

# Search for a core
arduino-cli core search esp32

# Install a specific version of the ESP32 core
arduino-cli core install esp32:esp32@2.0.17

# Search for a library
arduino-cli lib search "LibraryName"

# Install a specific version of a library
arduino-cli lib install "LibraryName"@1.x.x

# Show installed libraries
arduino-cli lib list

# Get board details
arduino-cli board details --fqbn esp32:esp32:esp32s3
```

---

# Getting Started with ESP32

- [ESP32 Getting Started Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/getting_started.html)
---

# Used Platform

- **Version**: [ESP32 Arduino Core v2.0.17](https://github.com/espressif/arduino-esp32/tree/2.0.17)
---

# Used Libraries

| Name                                                                                                          | Version |
|---------------------------------------------------------------------------------------------------------------|---------|
| [LovyanGFX](https://github.com/lovyan03/LovyanGFX)                                                            | 1.2.0   |
| [FastLED](https://github.com/FastLED/FastLED)                                                                 | 3.9.4   |
| [OneButton](https://github.com/mathertel/OneButton)                                                           | 2.6.1   |
| [USB](https://github.com/espressif/arduino-esp32/tree/2.0.17/libraries/USB)                                   | 2.0.0   |
| [WiFi](https://github.com/espressif/arduino-esp32/tree/2.0.17/libraries/WiFi)                                 | 2.0.0   |
| [PubSubClient](http://pubsubclient.knolleary.net)                                                             | 2.8     |
| [ArduinoJson](https://arduinojson.org/)                                                                       | 7.1.0   |
| [Preferences](https://github.com/espressif/arduino-esp32/tree/2.0.17/libraries/Preferences)                   | 2.0.0   |
| [base64_encode](https://github.com/dojyorin)                                                                  | 2.0.4   |
| [ArduinoWebsockets](https://github.com/gilmaimon/ArduinoWebsockets)                                           | 0.5.4   |
| [WiFiClientSecure](https://github.com/espressif/arduino-esp32/tree/2.0.17/libraries/WiFiClientSecure)         | 2.0.0   |
| [HTTPClient](https://github.com/espressif/arduino-esp32/tree/2.0.17/libraries/HTTPClient)                     | 2.0.0   |
| [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino)                                                    | 1.4.2   |
| [SimpleCLI](https://github.com/spacehuhntech/SimpleCLI)                                                       | 1.1.4   |
---

# Deprecated Libraries

| Name                                            | Version |
|-------------------------------------------------|---------|
| [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)  | 2.5.43  |
---