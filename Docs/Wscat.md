Here's a **tutorial on wscat** installation, usage, and a cheat sheet, along with the GitHub repository link: [wscat GitHub](https://github.com/websockets/wscat).

---

### **What is wscat?**
`wscat` is a simple WebSocket client and server tool implemented in Node.js. It allows you to connect to a WebSocket server, send and receive messages, and debug WebSocket connections.

---

### **Installation**

#### **Step 1: Install Node.js and npm**
First, ensure Node.js and npm (Node.js package manager) are installed on your Ubuntu system:
1. **Update the package list**:
   ```bash
   sudo apt update
   ```
2. **Install Node.js and npm**:
   ```bash
   sudo apt install nodejs npm -y
   ```

#### **Step 2: Install wscat**
1. Install `wscat` globally using npm:
   ```bash
   sudo npm install -g wscat
   ```

2. Verify the installation:
   ```bash
   wscat --version
   ```

---

### **Basic Usage**

#### **Connect to a WebSocket Server**
To connect to a WebSocket server, use the `-c` (connect) flag:
```bash
wscat -c ws://example.com:8232
wscat -c ws://192.168.50.206:8232
```

#### **Send a Message**
Once connected, type your message and press **Enter** to send it to the WebSocket server.

#### **Receive a Message**
When the WebSocket server sends a message, it will be displayed in the terminal.

#### **Close the Connection**
To close the WebSocket connection, press **Ctrl+C**.

---

### **wscat Cheat Sheet**

| **Command**                                   | **Description**                                                                                  |
|-----------------------------------------------|--------------------------------------------------------------------------------------------------|
| `wscat -c ws://example.com`                   | Connect to a WebSocket server.                                                                  |
| `wscat -c wss://example.com`                  | Connect to a secure WebSocket (WSS) server.                                                     |
| `wscat --help`                                | Display the help menu with all available options.                                               |
| `wscat -H "Authorization: Bearer <token>"`    | Send custom headers (e.g., for authentication).                                                 |
| `wscat -c ws://example.com --no-check`        | Disable SSL certificate validation (useful for testing).                                        |
| `wscat -c ws://example.com -p '{"foo":"bar"}'`| Send a JSON payload directly after connecting.                                                  |
| `wscat -l`                                    | Start a WebSocket server on localhost and wait for incoming connections.                        |
| `wscat -l -p 8080`                            | Start a WebSocket server on a specific port (e.g., 8080).                                       |
| `wscat -l --no-check`                         | Start a WebSocket server without SSL certificate validation.                                    |

---

### **Examples**

#### **Example 1: Simple Connection**
Connect to a public WebSocket server:
```bash
wscat -c ws://echo.websocket.org
```

Type any message, and the server will echo it back to you.

#### **Example 2: Send JSON Data**
Send JSON data to a WebSocket server:
```bash
wscat -c ws://example.com
{"message": "Hello, WebSocket!"}
```

#### **Example 3: Connect with Custom Header**
Connect to a WebSocket server with an `Authorization` header:
```bash
wscat -c ws://example.com -H "Authorization: Bearer YOUR_TOKEN"
```

#### **Example 4: Start a WebSocket Server**
Start a WebSocket server on port 3000:
```bash
wscat -l -p 3000
```

#### **Example 5: Debugging with Insecure SSL**
Connect to a WSS server with an invalid certificate:
```bash
wscat -c wss://example.com --no-check
```

---

### **Resources**
- Official GitHub Repository: [wscat GitHub](https://github.com/websockets/wscat)
- Public Echo Server for Testing: `ws://echo.websocket.org` (deprecated, alternatives may be required). 
