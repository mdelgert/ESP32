### Setup
```bash
platformio project init --board esp32-s3-devkitc-1 --project-dir ~/source/Test1 --ide vscode
cd src
touch main.cpp
pio run --target clean
pio run --target upload
pio debug --environment esp32-s3-devkitc-1
```

To create a PlatformIO project from the command line, you can use the `platformio` CLI. Here's a step-by-step guide:

### Steps to Create a PlatformIO Project

1. **Ensure PlatformIO CLI is Installed**  
   Make sure you have PlatformIO CLI installed. You can check by running:
   ```bash
   platformio --version
   ```
   If not installed, you can install it via `pip`:
   ```bash
   pip install platformio
   ```

2. **Navigate to Your Desired Folder**  
   Open a terminal and navigate to the directory where you want to create your project:
   ```bash
   cd /path/to/your/projects
   ```

3. **Run the `platformio project init` Command**  
   Use the following command to initialize a new PlatformIO project:
   ```bash
   platformio project init --board <board_id> --project-dir <project_folder>
   ```
   - Replace `<board_id>` with your target board's ID (e.g., `esp32dev`, `uno`). You can find the board ID from the PlatformIO [board list](https://platformio.org/boards).
   - Replace `<project_folder>` with the name of the new project folder or leave it out to initialize in the current directory.

   Example:
   ```bash
   platformio project init --board esp32dev --project-dir MyEsp32Project
   ```

4. **Optional Flags**  
   - `--ide`: Specify your preferred IDE (e.g., `vscode`, `clion`). This creates the necessary files for the IDE.
     ```bash
     platformio project init --board esp32dev --ide vscode
     ```
   - `--env`: Set the default environment name for the project.
   - `--examples`: Include examples if available.

5. **Navigate to Your New Project**  
   After running the command, navigate to the project folder:
   ```bash
   cd MyEsp32Project
   ```

6. **Start Coding**  
   Open the project in your IDE or edit the files manually:
   ```bash
   code .  # For Visual Studio Code
   ```

### Example Output
After creating a project, your folder structure will look like this:
```
MyEsp32Project/
├── platformio.ini
├── src/
│   └── main.cpp
└── lib/
```

- **`platformio.ini`**: The configuration file for your PlatformIO project.
- **`src/`**: Folder for your source code.
- **`lib/`**: Folder for any custom libraries.

Now you're ready to develop with PlatformIO!

