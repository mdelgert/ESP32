# To get board info
# esptool.py --chip esp32s3 --port /dev/ttyACM0 flash_id

# Merge the firmware
# esptool.py --chip esp32s3 --port /dev/ttyACM0 merge_bin \
#   -o .pio/build/esp32-s3-devkitc-1/merged-firmware.bin \
#   --flash_mode qio \
#   --flash_freq 40m \
#   --flash_size 16MB \
#   0x1000 .pio/build/esp32-s3-devkitc-1/bootloader.bin \
#   0x8000 .pio/build/esp32-s3-devkitc-1/partitions.bin \
#   0x10000 .pio/build/esp32-s3-devkitc-1/firmware.bin

# Erase the flash memory
#esptool.py --chip esp32s3 --port /dev/ttyACM0 erase_flash

# Upload the merged firmware
#esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z 0x1000 .pio/build/esp32-s3-devkitc-1/merged-firmware.bin
#esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z 0x1000 .pio/build/esp32-s3-devkitc-1/firmware_merged.bin

# Verify the firmware
#esptool.py --chip esp32s3 --port /dev/ttyACM0 verify_flash 0x1000 .pio/build/esp32-s3-devkitc-1/merged-firmware.bin

# Try flashing the individual components separately to isolate the problem:
# esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z \
#   0x1000 .pio/build/esp32-s3-devkitc-1/bootloader.bin \
#   0x8000 .pio/build/esp32-s3-devkitc-1/partitions.bin \
#   0x10000 .pio/build/esp32-s3-devkitc-1/firmware.bin

# # Erase the flash memory
# esptool.py --chip esp32s3 --port /dev/ttyACM0 erase_flash

# # Upload the bootloader
# esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z 0x1000 .pio/build/esp32-s3-devkitc-1/bootloader.bin

# # Upload the partition table
# esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z 0x8000 .pio/build/esp32-s3-devkitc-1/partitions.bin

# # Upload the application firmware
# esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z 0x10000 .pio/build/esp32-s3-devkitc-1/firmware.bin