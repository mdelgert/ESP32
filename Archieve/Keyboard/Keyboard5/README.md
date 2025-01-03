//.arduino15/packages/esp32/hardware/esp32/2.0.17/tools/sdk/esp32s2/include/arduino_tinyusb/tinyusb/src/class/hid/hid.h
// https://github.com/espressif/arduino-esp32/issues/8380

Here's a detailed explanation of the given commands using the `USBHIDKeyboard.h` library for an ESP32 or similar device configured to act as a USB HID keyboard:

### **1. Library Initialization**
The `USBHIDKeyboard.h` library is used to emulate a USB keyboard device. This enables the ESP32 to send keyboard input (key presses) to a connected computer, just like a physical keyboard.

---

### **2. Command Breakdown**

#### **`void setup()`**
The `setup()` function runs once when the device powers up or resets.

---

#### **`Keyboard.begin();`**
- Initializes the HID keyboard functionality.
- This prepares the device to start sending keyboard events to the host computer.

---

#### **`USB.begin();`**
- Starts the USB functionality.
- This initializes the USB communication between the ESP32 (or microcontroller) and the host computer.

---

#### **`delay(2000);`**
- Pauses the program for 2000 milliseconds (2 seconds).
- This gives the USB connection time to initialize and be recognized by the host system before sending key presses.

---

#### **`Keyboard.pressRaw(HID_KEY_GUI_LEFT);`**
- **`Keyboard.pressRaw`** sends a raw HID key press signal.
- `HID_KEY_GUI_LEFT` represents the **Left Windows Key** (or Command key on macOS).
- This simulates pressing the Left Windows key on the keyboard.

---

#### **`Keyboard.pressRaw(HID_KEY_R);`**
- Sends a raw HID key press for the letter "R".
- This key combination (`Win + R`) opens the **Run Dialog** on Windows.

---

#### **`delay(500);`**
- Waits for 500 milliseconds to ensure the key combination is registered by the operating system.

---

#### **`Keyboard.releaseRaw(HID_KEY_GUI_LEFT);`**
- Releases the **Left Windows Key**.
- Without this release, the system will consider the key still pressed.

---

#### **`Keyboard.releaseRaw(HID_KEY_R);`**
- Releases the **R key**.
- This completes the `Win + R` keypress sequence.

---

#### **`Keyboard.printf("notepad\n");`**
- Sends the string **`notepad`** followed by a newline (`\n`).
- This simulates typing the word `notepad` into the **Run Dialog** and pressing **Enter**.
- The **newline (`\n`)** acts as the Enter key.

---

### **Program Summary**
1. Initializes the USB HID keyboard and USB communication.
2. Simulates pressing **`Win + R`** to open the Run Dialog on Windows.
3. Types `notepad` and presses Enter to launch the Notepad application.

---

### **Output on the Host Computer**
When this code runs:
1. The Run Dialog (`Win + R`) opens.
2. `notepad` is typed into the dialog box.
3. The Enter key is pressed, launching the Notepad application.

---

This approach demonstrates how the `USBHIDKeyboard` library can automate keyboard input, useful for tasks like launching programs or sending predefined commands.