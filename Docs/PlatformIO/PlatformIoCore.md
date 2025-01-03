# Linux install
https://docs.platformio.org/en/latest/faq/install-python.html#faq-install-python
https://docs.platformio.org/en/latest/core/installation/shell-commands.html#piocore-install-shell-commands

```bash
sudo apt install python3 python3-venv curl
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
mkdir ~/.local/bin/
nano ~/.bashrc
# Add the following
# export PATH=$PATH:$HOME/.local/bin
ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
pio --version
sudo usermod -a -G dialout $USER
```
