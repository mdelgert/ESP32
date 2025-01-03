# See Setup.md for simplier process

# Easy setup PlatformIO core linking to extension rather than install
[Setup](https://docs.platformio.org/en/latest/core/installation/shell-commands.html#unix-and-unix-like)

[VSCODE extenstion](https://platformio.org/install/ide?install=vscode)

Install the extenstion then link in windows 

# Setting up PlatformIO IDE Extension for VS Code and Installing Core in WSL

Below are step-by-step instructions to install the PlatformIO IDE extension for VS Code and set up PlatformIO Core in WSL.

---

## **Step 1: Install VS Code**
1. Download and install [Visual Studio Code](https://code.visualstudio.com/).
2. Make sure you have installed the **Remote - WSL** extension for VS Code.
   - Go to the Extensions view (`Ctrl+Shift+X`) in VS Code.
   - Search for `Remote - WSL` and install it.

---

## **Step 2: Install PlatformIO IDE Extension**
1. Open VS Code and go to the Extensions view (`Ctrl+Shift+X`).
2. Search for **PlatformIO IDE**.
3. Install the extension from the [Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).
4. After installation, restart VS Code if prompted.

---

## **Step 3: Set Up PlatformIO Core in WSL**
### 3.1 Open WSL
1. Launch a terminal in WSL by opening VS Code and selecting **WSL: [Your Distro Name]** from the bottom-left corner.

### 3.2 Install Python
1. Check if Python is installed by running:
   ```bash
   python3 --version
   ```
2. If not installed, use your distribution’s package manager to install it:
   ```bash
   sudo apt update
   sudo apt install python3 python3-pip
   ```

### 3.3 Install PlatformIO Core
1. Use `pip` to install PlatformIO Core:
   ```bash
   python3 -m pip install platformio
   ```

2. Verify the installation by running:
   ```bash
   pio --version
   ```
   You should see the installed version of PlatformIO Core.

---

## **Step 4: Configure VS Code for PlatformIO in WSL**
1. Open a project folder in WSL using VS Code. You can use:
   ```bash
   code .
   ```
2. Ensure that PlatformIO is properly configured to work inside WSL:
   - Open the Command Palette (`Ctrl+Shift+P`).
   - Search for and run `PlatformIO: Build` to confirm integration.

---

## **Step 5: Create or Import a PlatformIO Project**
1. Use the **PlatformIO Home** button in the VS Code Activity Bar to:
   - Create a new project.
   - Import an existing project.

---

## **Troubleshooting**
1. If `pio` is not recognized in WSL, ensure Python is in your PATH:
   ```bash
   echo 'export PATH="$PATH:~/.local/bin"' >> ~/.bashrc
   source ~/.bashrc
   ```
2. If WSL does not recognize PlatformIO in VS Code, restart your machine and reopen WSL in VS Code.

---