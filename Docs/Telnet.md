On Ubuntu, you can use the **telnet** command-line utility to connect to servers over a network using the Telnet protocol. If Telnet is not installed by default on your system, follow these steps to install and use it.

---

### **Install Telnet**
Telnet is not included by default in most Ubuntu distributions. Install it with the following commands:

1. **Update the package list:**
   ```bash
   sudo apt update
   ```

2. **Install the telnet package:**
   ```bash
   sudo apt install telnet -y
   ```

3. **Verify the installation:**
   ```bash
   telnet --version
   ```

---

### **Basic Usage**

#### **1. Connect to a Server**
To connect to a server using Telnet, use the following syntax:
```bash
telnet <hostname or IP address> <port>
```
- Example:
  ```bash
  telnet example.com 80
  ```

#### **2. Send HTTP Requests (as an example)**
Once connected to port `80` (HTTP), you can send HTTP requests manually:
```plaintext
GET / HTTP/1.1
Host: example.com
```
Press **Enter** twice to send the request.

#### **3. Close a Telnet Session**
To close the connection, type:
```plaintext
quit
```
Or press `Ctrl+]`, then type `quit` and press **Enter**.

---

### **Common Telnet Commands**
While in a Telnet session, you can use the following commands:

| **Command**      | **Description**                                    |
|-------------------|----------------------------------------------------|
| `Ctrl+]`         | Enter Telnet command mode (escape character).      |
| `quit`           | Close the Telnet session.                         |
| `open`           | Open a connection to another host.                |
| `close`          | Close the current connection.                     |
| `status`         | Display the current status of the Telnet session. |
| `set`            | Set Telnet options.                               |
| `unset`          | Unset Telnet options.                             |

---

### **Example Use Cases**

#### **1. Test SMTP Server**
Connect to an SMTP server on port `25`:
```bash
telnet smtp.example.com 25
```
Send commands like `HELO`, `MAIL FROM`, and `RCPT TO` to test the server.

#### **2. Test Open Ports**
Check if a specific port is open:
```bash
telnet example.com 22
```

#### **3. Debug a Web Server**
Connect to a web server to debug:
```bash
telnet example.com 80
GET / HTTP/1.1
Host: example.com
```

---

### **Alternatives**
Telnet sends data in plain text, which is not secure. For modern systems, consider alternatives like:
1. **Netcat (nc):**
   ```bash
   nc <hostname> <port>
   ```
2. **OpenSSL (for secure connections):**
   ```bash
   openssl s_client -connect <hostname>:443
   ```

Using Telnet is mainly for testing and debugging legacy systems or open ports. For encrypted connections, always use secure protocols like SSH or HTTPS.