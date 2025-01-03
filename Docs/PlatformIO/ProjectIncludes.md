In your case, using `#include "Config.h"` is appropriate and aligns with common practices in C++ projects. Here’s why and the difference between `#include "Config.h"` and `#include <Config.h>`:

---

### **Difference Between `#include "..."` and `#include <...>`**

1. **`#include "..."`:**
   - This tells the compiler to first look for the file in the **current directory** (relative to the file including it).
   - If not found, it then searches in the **include paths** specified during the build process (e.g., `-I` flags in your `platformio.ini`).

   **Use Case:**
   - For your project-specific or local headers, like `Config.h` in your project.

   **Example:**
   ```cpp
   #include "Config.h"
   ```
   This is correct when `Config.h` is a file you’ve defined in your project, whether in `include/` or a library folder like `lib/`.

2. **`#include <...>`:**
   - This tells the compiler to search only in the **global include paths**, which are typically system paths or directories specified with `-I` in your build configuration.

   **Use Case:**
   - For standard library headers (e.g., `<iostream>`, `<vector>`).
   - For third-party library headers installed globally or provided by your toolchain.

   **Example:**
   ```cpp
   #include <iostream>
   ```

---

### **Proper Usage in Your Project**
For your project:
1. If `Config.h` is part of your project (e.g., in `include/` or a library like `lib/GfxHandler`), always use `#include "Config.h"`.
2. Reserve `#include <Config.h>` only if you plan to make `Config.h` part of a global or shared library (e.g., installed via a package manager).

---

### **Key Points for Consistency**
- **Within your project:** Use `#include "Config.h"` to avoid ambiguity and clearly signal that this is a local file.
- **For libraries or dependencies:** Use `#include <...>` if the header is from a third-party library.

---

### **Recommendation**
Stick with `#include "Config.h"` since it:
- Works with your current setup.
- Is more intuitive for other developers who might look at your code.
- Avoids unnecessary reliance on global include paths.

If all files in `src/` and `lib/` are working fine with `#include "Config.h"`, there’s no need to switch to angle brackets. Keep it consistent across your project!