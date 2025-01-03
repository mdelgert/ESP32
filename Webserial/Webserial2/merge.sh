# To get board info
# esptool.py --chip esp32s3 --port /dev/ttyACM0 flash_id

# esptool.py --chip esp32s3 --port /dev/ttyACM0 merge_bin \
#   -o merged-firmware.bin \
#   --flash_mode qio \
#   --flash_freq 40m \
#   --flash_size 16MB \
#   0x1000 bootloader.bin \
#   0x8000 partitions.bin \
#   0x10000 firmware.bin

esptool.py --chip esp32s3 --port /dev/ttyACM0 merge_bin \
  -o .pio/build/esp32-s3-devkitc-1/merged-firmware.bin \
  --flash_mode qio \
  --flash_freq 40m \
  --flash_size 16MB \
  0x1000 .pio/build/esp32-s3-devkitc-1/bootloader.bin \
  0x8000 .pio/build/esp32-s3-devkitc-1/partitions.bin \
  0x10000 .pio/build/esp32-s3-devkitc-1/firmware.bin