https://community.platformio.org/t/unable-to-debug-libpython2-7-so-1-0-missing-under-ubuntu-24-04-lts/40472/6
https://community.platformio.org/t/debug-aborts-with-python-error/41139
https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/linux-macos-setup.html
https://community.platformio.org/t/debug-aborts-with-python-error/41139/2

[env:esp32dev]
; Arduino-ESP32 3.0.5
platform = https://github.com/pioarduino/platform-espressif32/releases/download/51.03.05/platform-espressif32.zip
board = esp32dev
framework = arduino

```bash
mkdir ~/esp
cd ~/esp
git clone -b v5.2.2 --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh esp32s3
cd ~/.platformio/packages/toolchain-xtensa-esp32s3/bin
mv xtensa-esp32s3-elf-gdb xtensa-esp32s3-elf-gdb.orig
cp ~/.espressif/tools/xtensa-esp-elf-gdb/14.2_20240403/xtensa-esp-elf-gdb/bin/xtensa-esp32s3-elf-gdb xtensa-esp32s3-elf-gdb
cp ~/.espressif/tools/xtensa-esp-elf-gdb/14.2_20240403/xtensa-esp-elf-gdb/bin/xtensa-esp-elf-gdb-no-python .
cp ~/.espressif/tools/xtensa-esp-elf-gdb/14.2_20240403/xtensa-esp-elf-gdb/lib/xtensa_esp32s3.so ../lib
```