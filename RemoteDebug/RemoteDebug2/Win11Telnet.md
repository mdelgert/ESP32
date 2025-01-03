### README: Installing Telnet on Windows 11 via PowerShell

This guide will walk you through enabling the Telnet client on Windows 11 using PowerShell.

---

### Prerequisites
- **Administrator privileges** are required to enable the Telnet client.

---

### Steps to Install Telnet

1. **Open PowerShell as Administrator**
   - Press `Win + S` to open the search bar.
   - Type `PowerShell`.
   - Right-click **Windows PowerShell** and select **Run as administrator**.

2. **Run the Installation Command**
   Copy and paste the following command into the PowerShell window and press `Enter`:
   ```powershell
   dism /online /Enable-Feature /FeatureName:TelnetClient
   ```

3. **Wait for the Installation to Complete**
   - You will see a progress bar. Once it reaches 100%, you should see:
     ```
     [==========================100.0%==========================]
     The operation completed successfully.
     ```

4. **Verify the Installation**
   - Type `telnet` in the same PowerShell window and press `Enter`.
   - If Telnet is installed, you will see the Telnet prompt:
     ```
     Microsoft Telnet>
     ```

---

### How to Use Telnet
To connect to a remote server, type:
```cmd
telnet [IP_ADDRESS or HOSTNAME]
```
Example:
```cmd
telnet 192.168.50.x
```

---

### Notes
- Telnet is not secure. All communication is sent in plaintext.
- Use Telnet only for trusted networks or testing purposes.
- For secure alternatives, consider using SSH.

---
