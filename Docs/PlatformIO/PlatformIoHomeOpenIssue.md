# PlatformIO IDE extension does not work with Remote Development using SSH
https://github.com/platformio/platformio-vscode-ide/issues/942
https://github.com/luxk3/ubuntu_server_remote_dev_platformio

Run platform IO home in browser
```bash
pio home --no-open
pio home # To launch
sudo lsof -i :8008
kill id
```

Update vscode file 
preferences -> settings 
-> Remote Extenstions -> platformIO 
-> Pio Home Server Http Port -> 8008

Add port forward in ssh config
Host example
	HostName example
	User user
	LocalForward 127.0.0.1:8008 127.0.0.1:8008
	IdentityFile ~/.ssh/key
	IdentitiesOnly yes

