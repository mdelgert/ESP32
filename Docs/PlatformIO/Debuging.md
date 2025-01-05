# Debugging setup
https://github.com/jake-is-ESD-protected/ESP32debugging_guide
https://www.youtube.com/watch?v=b1VkJODi_4w&t=732s
https://www.youtube.com/watch?v=ENLhW0MQuu0&t=81s

```bash
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
sudo usermod -a -G dialout $USER
sudo usermod -a -G plugdev $USER
#sudo service restart udev
sudo udevadm control --reload-rules
sudo udevadm trigger
```