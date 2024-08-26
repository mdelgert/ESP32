# Arduino CLI
https://arduino.github.io/arduino-cli/0.36/
https://www.devdungeon.com/content/arduino-cli-tutorial

# Install
```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/.local/bin sh
arduino-cli version
```

# Upload
```bash
arduino-cli config init # Init arduino client
arduino-cli sketch new MyFirstSketch # Create a sketch
arduino-cli core update-index # Update to current board indexs
arduino-cli core search m5stack # Search for m5stack board
arduino-cli core install m5stack:esp32 # Install m5stack board support
arduino-cli core list # Show core boards installed
arduino-cli board list # Show boards plugged in
arduino-cli board listall # Show FQBN
arduino-cli board listall M5 # Search FQBN for M5
arduino-cli compile --fqbn m5stack:esp32:m5stack_atom MyFirstSketch # Compile a sketch
arduino-cli upload --port /dev/ttyUSB0 --fqbn m5stack:esp32:m5stack_atom MyFirstSketch # Upload a sketch
```

# Install library dependencies
```bash
arduino-cli lib search m5stack # Search for a library 
arduino-cli lib install "M5Stack" # Install a library
arduino-cli lib list # Confirm it is installed with
``
# Setup
https://support.arduino.cc/hc/en-us/articles/360016495679-Fix-port-access-on-Linux
sudo apt install libfuse2 python3-pip
#pip install pyserial
sudo apt install python3-serial
sudo usermod -a -G dialout <username>
(Restart your computer for the changes to take effect.)

# Shortcut
sudo wget https://raw.githubusercontent.com/mdelgert/ReferenceNotes/main/arduino2.png /usr/share/icons/arduino2.png
sudo nano ~/.local/share/applications/arduino.desktop
sudo chmod +x ~/.local/share/applications/arduino.desktop

# Example
[Desktop Entry]
Name=Arduino
Exec=/home/mdelgert/Downloads/arduino-ide_2.3.2_Linux_64bit.AppImage
Icon=/usr/share/icons/arduino2.png
Type=Application
Categories=Development;

# Boards
https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json