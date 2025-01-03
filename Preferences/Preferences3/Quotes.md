When you input a password with quotes, such as `set password1 passwordwithquotes"123`, the issue arises because **quotes** are treated as part of the CLI input parsing, breaking the arguments.

To fix this, we need to handle quotes properly in the **SimpleCLI** library and **escape the quotes** in the input. Here’s the updated solution:

---

## **Fixing the Issue**

1. Modify how the CLI parses arguments with quotes by:
   - Removing unnecessary surrounding quotes (`"`) or escaping them properly.
   - Supporting escaped characters like `\"`.

2. Update the `set` command to handle **quoted strings** correctly, so the input:
   ```plaintext
   set password1 "passwordwithquotes\"123"
   ```
   will work as intended.

---

### **Updated Sketch**

This version supports quotes in values by manually processing the `set` command's input.

```cpp
#include <Preferences.h>
#include <SimpleCLI.h>

Preferences preferences;
SimpleCLI cli;

// Command declarations
Command setCmd, getCmd, eraseCmd, listCmd, helpCmd;

// Function Prototypes
void setupCommands();
void setCallback(cmd* c);
void getCallback(cmd* c);
void eraseCallback(cmd* c);
void listCallback(cmd* c);
void helpCallback(cmd* c);
String cleanQuotedInput(const String& input);

void setup() {
  Serial.begin(115200);
  preferences.begin("app", false); // Start Preferences namespace

  setupCommands();
  Serial.println("Welcome! Use 'help' for available commands.");
}

void loop() {
  while (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    cli.parse(input);
  }
}

// Initialize CLI Commands
void setupCommands() {
  setCmd = cli.addCmd("set", setCallback);
  setCmd.addPositionalArgument("key");
  setCmd.addPositionalArgument("value");

  getCmd = cli.addCmd("get", getCallback);
  getCmd.addPositionalArgument("key");

  eraseCmd = cli.addCmd("erase", eraseCallback);
  eraseCmd.addPositionalArgument("key", "");

  listCmd = cli.addCmd("list", listCallback);
  helpCmd = cli.addCmd("help", helpCallback);
}

// Clean input to handle quotes
String cleanQuotedInput(const String& input) {
  String cleaned = input;
  cleaned.trim(); // Remove leading/trailing spaces
  if (cleaned.startsWith("\"") && cleaned.endsWith("\"")) {
    cleaned = cleaned.substring(1, cleaned.length() - 1);
  }
  cleaned.replace("\\\"", "\""); // Handle escaped quotes
  return cleaned;
}

// Set Key-Value Pair
void setCallback(cmd* c) {
  Command cmd(c);
  String key = cmd.getArgument("key").getValue();
  String value = cmd.getArgument("value").getValue();

  value = cleanQuotedInput(value); // Clean the input value
  preferences.putString(key.c_str(), value);

  Serial.print("Saved: ");
  Serial.print(key);
  Serial.print(" = ");
  Serial.println(value);
}

// Get Value
void getCallback(cmd* c) {
  Command cmd(c);
  String key = cmd.getArgument("key").getValue();
  String value = preferences.getString(key.c_str(), "");

  if (value != "") {
    Serial.print(key);
    Serial.print(" = ");
    Serial.println(value);
  } else {
    Serial.println("Key not found or empty.");
  }
}

// Erase Keys
void eraseCallback(cmd* c) {
  Command cmd(c);
  String key = cmd.getArgument("key").getValue();

  if (key == "") {
    preferences.clear();
    Serial.println("All keys erased.");
  } else {
    preferences.remove(key.c_str());
    Serial.print("Key erased: ");
    Serial.println(key);
  }
}

// List All Saved Keys and Values (Simulated)
void listCallback(cmd* c) {
  Serial.println("Listing keys is not directly supported in Preferences.");
  Serial.println("Use consistent key names like password1, password2, etc.");
}

// Help Command
void helpCallback(cmd* c) {
  Serial.println("Commands:");
  Serial.println("  set <key> <value>   - Save key-value pair (use \"\" for quotes).");
  Serial.println("  get <key>           - Retrieve value for key.");
  Serial.println("  erase [key]         - Erase specific key or all keys.");
  Serial.println("  list                - List all keys (simulate).");
  Serial.println("  help                - Show help message.");
}
```

---

### **Key Changes**
1. **`cleanQuotedInput` Function**:
   - Removes surrounding quotes (`"`) and handles escaped quotes (`\"`).

2. **Set Command Input**:
   - When you input a value like `set password1 "myPassword\"123"`, it properly saves `myPassword"123` to Preferences.

3. **Escaped Characters**:
   - Supports escaped quotes (`\"`) within the value.

---

### **Usage**

**Set a value with quotes:**
```plaintext
set password1 "passwordwithquotes\"123"
```

**Get the value:**
```plaintext
get password1
```

**Output:**
```plaintext
password1 = passwordwithquotes"123
```

**Set a value without quotes:**
```plaintext
set password2 plainpassword123
```

**Erase a specific key:**
```plaintext
erase password1
```

---

### **Why This Works**
- The `cleanQuotedInput` ensures values with quotes are handled properly without breaking the argument parsing.
- Values are saved and retrieved using `preferences.putString` and `preferences.getString`.

---

### **Test Cases**
| Input                           | Saved Value             |
|---------------------------------|-------------------------|
| `set password1 "abc\"123"`      | `abc"123`              |
| `set password2 plainpassword`   | `plainpassword`         |
| `set key1 "value with spaces"`  | `value with spaces`     |
| `set key2 "escaped \\\" quote"` | `escaped \" quote`      |

This solution makes the `set` command flexible and ensures it works seamlessly with passwords or values containing quotes and spaces. Let me know if you need further enhancements! 🚀