To format C++ code in Visual Studio Code, follow these steps:

### Step 1: Install C++ Extension
1. Open **Extensions** in Visual Studio Code (Ctrl+Shift+X).
2. Search for and install the **C/C++** extension by Microsoft.

### Step 2: Install a Code Formatter
The **C/C++** extension supports formatting with:
- **Clang-Format** (recommended)
- **Custom formatters** if configured.

To install **Clang-Format**:
- On **Windows**: Use a package manager like [winget](https://docs.microsoft.com/en-us/windows/package-manager/winget/) or download from the [LLVM website](https://llvm.org/).
- On **Linux**: Run `sudo apt install clang-format` or use your package manager.
- On **macOS**: Use Homebrew: `brew install clang-format`.

### Step 3: Configure Formatting
1. Open your **Settings** (Ctrl+,).
2. Search for `editor.defaultFormatter`.
3. Set the formatter to `ms-vscode.cpptools` or the specific formatter you've installed.
4. Alternatively, update your workspace settings in `settings.json`:
    ```json
    {
        "[cpp]": {
            "editor.defaultFormatter": "ms-vscode.cpptools",
            "editor.formatOnSave": true
        }
    }
    ```

### Step 4: Format Code
- **Format Selection**: Highlight the code and press `Ctrl+K Ctrl+F`.
- **Format Entire File**: Press `Shift+Alt+F` (or `Ctrl+Shift+I` on macOS).

### Step 5: Customize Clang-Format
1. Create a `.clang-format` file in the root of your project directory.
2. Define your formatting style, for example:
    ```yaml
    BasedOnStyle: Google
    IndentWidth: 4
    UseTab: Never
    ```
3. Format your code, and it will adhere to the `.clang-format` settings.

### Optional: Use Formatting Keybindings
You can customize the keybindings for formatting by navigating to **File → Preferences → Keyboard Shortcuts** and searching for `format`. 

Let me know if you need help with `.clang-format` styles or further setup!