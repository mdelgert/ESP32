To upload and run code using the PlatformIO extension in VS Code, follow these steps:

### 1. **Verify Your Setup**
   - Ensure you have installed the PlatformIO extension in VS Code.
   - Check that the appropriate development environment and toolchain for your board are installed. PlatformIO usually handles this when you open a project or create one.

### 2. **Open the Sample Project**
   - Open the sample project in VS Code by navigating to the project folder.
   - Confirm the project structure is correct. You should see a `platformio.ini` file in the root of the project. This file defines the board, platform, and frameworks.

### 3. **Connect Your Device**
   - Connect your development board (e.g., ESP32, Arduino) to your computer via USB.
   - Ensure the correct drivers for your board are installed. PlatformIO can often auto-detect the connected device.

### 4. **Configure the Project**
   - Open the `platformio.ini` file and verify:
     - The correct `board` is specified (e.g., `esp32dev` for ESP32 DevKit boards).
     - The appropriate `upload_port` is defined if auto-detection fails (you can manually set it to the COM port or `/dev/tty` used by your board).

     Example:
     ```ini
     [env:esp32dev]
     platform = espressif32
     board = esp32dev
     framework = arduino
     upload_port = COM3  ; Adjust based on your system
     ```

### 5. **Upload and Run the Code**
   - Open the **PlatformIO Toolbar**:
     - Look for the PlatformIO logo in the bottom-left corner of VS Code or press `Ctrl+Shift+P` (or `Cmd+Shift+P` on macOS) and search for `PlatformIO: Upload`.
   - Alternatively, use these **keyboard shortcuts**:
     - **Build** the project: `Ctrl+Alt+B` (or `Cmd+Option+B` on macOS).
     - **Upload** the code: `Ctrl+Alt+U` (or `Cmd+Option+U` on macOS).

   PlatformIO will:
   - Compile your code.
   - Upload it to the board.
   - Reset the board to run the uploaded code.

### 6. **Monitor the Serial Output**
   - Use the PlatformIO Serial Monitor to check output from your board:
     - Open the PlatformIO Toolbar and select **Monitor** or press `Ctrl+Alt+M` (or `Cmd+Option+M` on macOS).
     - Ensure the correct baud rate (e.g., `115200`) is set in the `platformio.ini` file.

     Example:
     ```ini
     monitor_speed = 115200
     ```

### 7. **Troubleshooting**
   - **Device Not Found:** Ensure the correct USB cable is used (data cables, not power-only).
   - **Permission Issues (Linux):** Add your user to the `dialout` group if you encounter permission errors:
     ```bash
     sudo usermod -aG dialout $USER
     ```
     Then restart your machine.
   - **Upload Fails:** Check the `upload_speed` setting in `platformio.ini`, or try holding the `BOOT` button (if available) during upload.

Once you successfully upload the code, it should automatically start running on the device. Use the serial monitor to interact with or observe the device's behavior.

The error occurs because your system uses a managed Python environment, which restricts global installation of packages via `pip` to prevent system instability. Here's how to resolve it safely:

---

### **Option 1: Use a Virtual Environment (Recommended)**
Create a Python virtual environment for PlatformIO to avoid system conflicts:
1. **Create the Virtual Environment**:
   ```bash
   python3 -m venv ~/platformio-venv
   ```
   This creates a virtual environment in the `~/platformio-venv` directory.

2. **Activate the Virtual Environment**:
   ```bash
   source ~/platformio-venv/bin/activate
   ```

3. **Install PlatformIO**:
   ```bash
   pip install platformio
   ```

4. **Run PlatformIO Commands**:
   With the virtual environment active, run your commands:
   ```bash
   pio run -e esp32-s3-devkitc-1 -t upload
   ```

5. **Deactivate the Environment** (When Done):
   Exit the virtual environment with:
   ```bash
   deactivate
   ```

---

### **Option 2: Use pipx for Isolated Installation**
`pipx` is a tool that installs Python applications in isolated environments, managing dependencies safely.

1. **Install pipx**:
   ```bash
   sudo apt install pipx
   ```

2. **Install PlatformIO Using pipx**:
   ```bash
   pipx install platformio
   ```

3. **Run PlatformIO Commands**:
   Once installed, you can use PlatformIO directly:
   ```bash
   pio run -e esp32-s3-devkitc-1 -t upload
   ```

---

### **Option 3: Override System Restriction (Not Recommended)**
You can override the restriction, but this may break your system’s Python environment:
1. Add `--break-system-packages` to the `pip install` command:
   ```bash
   pip install platformio --break-system-packages
   ```
   Proceed with caution as this can cause system instability.

---

### **Option 4: Use PlatformIO in Docker**
If you prefer to avoid modifying your system, you can use PlatformIO within a Docker container:
1. **Pull the PlatformIO Docker Image**:
   ```bash
   docker pull platformio/platformio-core
   ```

2. **Run PlatformIO Commands in the Container**:
   Replace `<project_dir>` with your project path:
   ```bash
   docker run --rm -v <project_dir>:/workspace -it platformio/platformio-core pio run -e esp32-s3-devkitc-1 -t upload
   ```

---

### **Final Notes**
- The **virtual environment** method (Option 1) is the safest and most flexible approach.
- Ensure your user has access to the required device (e.g., `/dev/ttyACM0`):
   ```bash
   sudo usermod -aG dialout $USER
   ```
   Then, log out and back in.

If you still encounter issues, let me know!