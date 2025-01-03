# Enable serial debugging
#arduino-cli compile --fqbn esp32:esp32:esp32s3:CDCOnBoot=cdc OTA1.ino

# Set CPU frequency to 240 MHz
arduino-cli compile --fqbn esp32:esp32:esp32s3:CPUFreq=240 OTA1.ino

#arduino-cli upload --port /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 OTA1.ino
#arduino-cli upload -p 192.168.50.117 --fqbn esp32:esp32:esp32s3 OTA1.ino
#arduino-cli upload -p 192.168.50.117 --fqbn esp32:esp32:esp32s3 --upload-field password="123" OTA1.ino
arduino-cli upload --fqbn esp32:esp32:esp32s3:CPUFreq=240 -p 192.168.50.117 --protocol network --upload-field password="123" OTA1.ino

# Arduino CLI is attempting to use a serial protocol instead of the network protocol for the OTA upload on WSL 2. 
# Explicitly set the protocol to network. Does not work.
#arduino-cli upload -p 192.168.50.117 --fqbn esp32:esp32:esp32s3 --protocol network --upload-field password="123" OTA1.ino

