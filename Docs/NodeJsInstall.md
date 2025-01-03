# Download and install nvm:
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash

# Download and install Node.js:
nvm install 18

# Verify the Node.js version:
node -v # Should print "v18.20.5".
nvm current # Should print "v18.20.5".

# Verify npm version:
npm -v # Should print "10.8.2".
