Here's a streamlined cheat sheet for working with PlatformIO entirely via the **Command-Line Interface (CLI)**, assuming it’s already installed:

---

### **Step 1: Initialize the Project**
Run the following command to create a new PlatformIO project for the ESP32-S3-DevKitC-1:

```bash
pio project init --board esp32-s3-devkitc-1 --project-option "platform=espressif32@6.9.0" --project-option "framework=arduino"
```

- **Creates the directory structure**:
  - `platformio.ini`
  - `src/`, `lib/`, `include/`, etc.
- Configures the `esp32-s3-devkitc-1` board with the specified platform and Arduino framework.

---

### **Step 2: Configure `platformio.ini`**
Modify the `platformio.ini` file (found in the project root) with the following content:

```ini
[env:esp32-s3-devkitc-1]
platform = espressif32@6.9.0
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
upload_port = /dev/ttyACM0
build_flags = 
    -DARDUINO_USB_MODE=1       ; Enable USB CDC mode
    -DARDUINO_USB_CDC_ON_BOOT=1 ; USB CDC on boot
```

---

### **Step 3: Add Libraries**
#### Add a Specific Library Version:
Install libraries using the following command:

```bash
pio lib install "Adafruit NeoPixel@1.11.0"
```

This updates the `platformio.ini` file with:
```ini
lib_deps =
    Adafruit NeoPixel@1.11.0
```

---

### **Step 4: Add Source Code**
Create a simple sketch in `src/main.cpp`:

```bash
nano src/main.cpp
```

Paste the following code:
```cpp
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Setup complete!");
}

void loop() {
    Serial.println("Hello from ESP32-S3!");
    delay(1000);
}
```

Save and exit.

---

### **Step 5: Build, Upload, and Monitor**
#### **Build the Project**:
Compile the code:
```bash
pio run
```

#### **Clean Build Files**:
Remove all compiled files:
```bash
pio run --target clean
```

#### **Upload the Firmware**:
Flash the compiled binary to the board:
```bash
pio run --target upload
```

#### **Monitor Serial Output**:
Start the serial monitor:
```bash
pio device monitor --baud 115200
```

#### **Combine Build and Upload**:
```bash
pio run --target upload
```

---

### **Step 6: Get Board Features**
#### List Connected Devices:
Find connected boards and ports:
```bash
pio device list
```

---

### **Directory Structure**
After initialization, the project directory structure will look like this:
```
.
├── platformio.ini    # Main configuration file
├── src/              # Source code (e.g., main.cpp)
├── include/          # Header files
├── lib/              # Manually added libraries
├── .pio/             # Build artifacts (auto-generated)
└── test/             # Unit tests
```

---

### **Essential Commands**
- **Initialize Project**:
  ```bash
  pio project init --board esp32-s3-devkitc-1
  ```
- **Build**:
  ```bash
  pio run
  ```
- **Clean**:
  ```bash
  pio run --target clean
  ```
- **Upload**:
  ```bash
  pio run --target upload
  ```
- **Monitor Serial**:
  ```bash
  pio device monitor --baud 115200
  ```
- **List Devices**:
  ```bash
  pio device list
  ```
- **Add Library**:
  ```bash
  pio lib install "LibraryName@Version"
  ```

Now you're ready to efficiently work with your ESP32-S3 board using PlatformIO CLI! 🚀