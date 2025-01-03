Setup user and sudo

```bash
apt update
apt install sudo
# Add a new user
sudo adduser newusername
# Set the password for the new user
sudo passwd newusername
# Add the user to the sudo group
sudo usermod -aG sudo newusername
su newusername
cd ~
mkdir .ssh
cd .ssh
touch authorized_keys
# Add ssh key
nano authorized_keys
# Remove password requirement for sudo
sudo visudo
# Add the following line at the end of the file
newusername ALL=(ALL) NOPASSWD:ALL
```

Setup dev

https://docs.platformio.org/en/latest/faq/install-python.html
```bash
sudo apt install git python3 python3-venv
git config --global user.name "John Doe"  
git config --global user.email johndoe@example.com  
git config --list
cd ~/.ssh
touch config
nano config
# chmod 600 ensures that only the owner of the file can read and write it, and no one else can access it.
chmod 600 yourkey
# enable serial access
sudo usermod -a -G dialout <username>
```