https://github.com/esphome/esphome/blob/dev/esphome/components/esp32_improv/automation.h
https://github.com/improv-wifi/sdk-cpp/tree/main
https://www.npmjs.com/package/esp-web-tools
https://github.com/espressif/esptool?tab=readme-ov-file
https://blog.spacehuhn.com/espwebtool
https://github.com/SpacehuhnTech/espwebtool

```bash
sudo apt update
sudo apt install python3 python3-pip -y
#pip install esptool
#apt install python3-esptool
sudo apt install pipx -y
python3 -m pipx ensurepath
pipx install esptool
esptool.py --version
```

esptool.py --chip esp32-s3 merge_bin \
  -o merged-firmware.bin \
  --flash_mode dio \
  --flash_freq 40m \
  --flash_size 8MB \
  0x1000 bootloader.bin \
  0x8000 partitions.bin \
  0xe000 firmware.bin