# Test connection
sudo apt install node-ws
wscat -c wss://echo.websocket.org/

# Get the cert
openssl s_client -connect echo.websocket.org:443 -showcerts

# For azure get SHA256 the secound cert
openssl s_client -connect yourapp.azurewebsites.net:443 -showcerts