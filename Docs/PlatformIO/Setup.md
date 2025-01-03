##### Note for MAC install with brew #############

Here's how to set the PlatformIO CLI path as a **system environment variable** directly using PowerShell commands:

```markdown
# PlatformIO Setup Instructions

## 1. Install PlatformIO Extension
1. Open **Visual Studio Code**.
2. Go to the **Extensions Marketplace** (Ctrl+Shift+X or click on the Extensions icon).
3. Search for `PlatformIO IDE`.
4. Click **Install** to add the extension.
5. Restart Visual Studio Code after installation.

---

## 2. Link PlatformIO Core CLI to System PATH (Windows PowerShell)

1. Open **PowerShell** as Administrator.

2. Set the `Path` environment variable to include the PlatformIO CLI folder:
   ```powershell
   [System.Environment]::SetEnvironmentVariable("Path", "$($env:Path);$env:USERPROFILE\.platformio\penv\Scripts", [System.EnvironmentVariableTarget]::Machine)
   ```

   - This command adds `C:\Users\<YourUserName>\.platformio\penv\Scripts` to the **system-wide PATH variable**.
   - Replace `$env:USERPROFILE` with the actual path if needed (e.g., `C:\Users\mdelgert`).

3. Confirm the change:
   ```powershell
   [System.Environment]::GetEnvironmentVariable("Path", [System.EnvironmentVariableTarget]::Machine)
   ```

   Ensure the `PlatformIO` path (`C:\Users\<YourUserName>\.platformio\penv\Scripts`) is listed.

4. Restart your computer or any open terminal to apply the changes.

---

## 3. Verify Installation
Run the following command in PowerShell:
```powershell
pio --version
```

You should see the PlatformIO Core version number.

---

Done! 🎉 PlatformIO is now installed and linked as a system-wide environment variable via PowerShell.
```

Here’s the updated guide for Ubuntu and macOS, including the steps mentioned in your reference:

```markdown
# PlatformIO Setup Instructions for Ubuntu and macOS

## 1. Export `$HOME/.local/bin` to PATH

## For mac use brew - https://formulae.brew.sh/formula/platformio#default
```bash
brew install platformio
```

### For Bash
1. Open a terminal.
2. Edit your `~/.bashrc`, `~/.bash_profile` or `~/.profile` file:
   ```bash
   nano `~/.bashrc`, ~/.bash_profile or `nano ~/.profile`
   ```
3. Add the following line to export `$HOME/.local/bin` to your PATH if it doesn't exsists.
   ```bash
   export PATH=$PATH:$HOME/.local/bin
   ```
4. Save the file and reload the profile:
   ```bash
   source ~/.bash_profile  # Or `source ~/.profile`
   ```

### For Zsh
1. Edit your `~/.zprofile` file:
   ```bash
   nano ~/.zprofile
   ```
2. Add the following line to source your Bash profile for compatibility:
   ```bash
   emulate sh -c '. ~/.profile'
   ```
3. Save the file and reload the profile:
   ```bash
   source ~/.zprofile
   ```

---

## 2. Create Symbolic Links for PlatformIO Executables
1. Create the necessary symlinks in `$HOME/.local/bin`:
   ```bash
   mkdir -p ~/.local/bin  # Ensure the directory exists
   ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
   ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
   ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
   ```

   Or run ./Setup.sh 

---

## 3. Restart Your Session
1. Log out and log back in, or restart your terminal.

---

## 4. Verify Installation
1. Test the PlatformIO CLI by running:
   ```bash
   pio --version
   ```
   You should see the PlatformIO Core version number.

---

Done! 🎉 PlatformIO is now installed and configured to be accessible globally from any terminal session.

## 99-platformio-udev.rules
(link)[https://docs.platformio.org/en/latest/core/installation/udev-rules.html]
```

