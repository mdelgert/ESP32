The error `Bad CPU type in executable` typically occurs when attempting to run a binary compiled for a different architecture than your system's CPU. Since you're using an Apple Silicon Mac (M1), this error suggests that the `esptool` binary in the ESP32 Arduino platform is not compatible with ARM-based processors.

### Solution

1. **Verify Compatibility of ESP32 Tools**
   - The ESP32 toolchain might be targeting Intel (x86_64) binaries, which are incompatible with Apple Silicon (ARM64) without emulation.

2. **Install Rosetta 2**
   - If not already installed, Rosetta 2 can help run x86_64 binaries on an Apple Silicon Mac.
   - Run the following command in your terminal:
     ```bash
     softwareupdate --install-rosetta
     ```
   - Retry the `arduino-cli compile` command.

3. **Reinstall ESP32 Board Package**
   - Ensure that the tools are downloaded and compiled for the correct architecture:
     ```bash
     arduino-cli core uninstall esp32:esp32
     arduino-cli core update-index
     arduino-cli core install esp32:esp32
     ```
   - This ensures you have the latest version and potentially fixes architecture-related issues.

4. **Manually Replace `esptool`**
   - Download a compatible version of `esptool` for Apple Silicon from the official repository:
     - Repository: [esptool GitHub](https://github.com/espressif/esptool)
     - Installation using pip (recommended):
       ```bash
       python3 -m pip install esptool
       ```
     - Replace the binary in the path `/Users/mdelgert/Library/Arduino15/packages/esp32/tools/esptool_py/4.5.1/` with the one installed via pip or ensure the path uses the pip-installed version.

5. **Verify Installation**
   - Test if `esptool` works by running:
     ```bash
     esptool.py --help
     ```
   - If successful, retry compiling your sketch.

6. **Check Architecture of `esptool`**
   - Verify the architecture of the problematic `esptool` binary:
     ```bash
     file /Users/mdelgert/Library/Arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool
     ```
   - If it shows `x86_64`, it's incompatible with Apple Silicon unless you use Rosetta.

7. **Force Arduino CLI to Use the Python `esptool`**
   - Set the environment variable to point Arduino CLI to the compatible `esptool` installed via pip:
     ```bash
     export PATH="/path/to/python-installed-esptool:$PATH"
     ```

### If the Problem Persists
- Ensure you're using the latest version of Arduino CLI:
  ```bash
  arduino-cli version
  ```
  Upgrade if necessary:
  ```bash
  brew upgrade arduino-cli
  ```
- If the issue persists, let me know, and we can explore further debugging options.