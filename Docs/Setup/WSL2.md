# WSL2 Arduino CLI Setup - https://github.com/arduino/arduino-cli?tab=readme-ov-file
```bash
cd ~
mkdir .local
cd .local
mkdir bin
nano ~/.bashrc
# Add the following
export PATH="$PATH:$HOME/.local/bin"
# Reload bashrc
source ~/.bashrc
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/.local/bin sh
arduino-cli version
# For network uploads does not appear to work easy in WSL2
# sudo apt install python3 python3-pip pipx
# python3 --version
# pip3 --version
# pipx install esptool
# esptool.py version
```

# WSL2 Install USBIP - https://github.com/dorssel/usbipd-win
```PS
winget install usbipd
# Note close all VSCODE instances before running the following with elevated PS
usbipd list
# Example
usbipd bind --busid=6-1
# Verify usbipd list
usbipd list
# Note if disconnect will have to run again
usbipd attach --wsl --busid=6-1
# To detach all
usbipd detach -a 
# VSCODE extenstion to make it easier - https://marketplace.visualstudio.com/items?itemName=thecreativedodo.usbip-connect
```

# WSL2 Serial setup install VSCODE Serial Monitor
```bash
sudo usermod -a -G dialout $USER
sudo apt install usbutils
lsusb
# In serial monitor should see device example /dev/ttyACM0
```