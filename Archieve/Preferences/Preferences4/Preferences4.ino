#include <Preferences.h>
#include <SimpleCLI.h>

// Libraries: Preferences for persistent storage, SimpleCLI for command handling

// Preferences and CLI Objects
Preferences preferences;
SimpleCLI cli;

// Version
const char* VERSION = "1.0.0";

// Command Handlers
void helpHandler(cmd* c);
void versionHandler(cmd* c);
void setHandler(cmd* c);
void getHandler(cmd* c);
void listHandler(cmd* c);
void eraseHandler(cmd* c);

// Function Declarations
void addCommands();
void handleCommand(String input);
void printPreferences();

void setup() {
  Serial.begin(115200);

  // Initialize Preferences
  preferences.begin("settings", false);

  // Initialize CLI and add commands
  addCommands();
  Serial.println("\nESP32-S3 CLI Ready. Type 'help' for a list of commands.");
}

void loop() {
  // Check for Serial Input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    handleCommand(input);
  }
}

// ==========================
// Command Initialization
// ==========================
void addCommands() {
  cli.addCmd("help", helpHandler);
  cli.addCmd("version", versionHandler);

  Command setCommand = cli.addCmd("set", setHandler);
  setCommand.addPosArg("key");
  setCommand.addPosArg("value");

  Command getCommand = cli.addCmd("get", getHandler);
  getCommand.addPosArg("key");

  cli.addCmd("list", listHandler);
  cli.addCmd("erase", eraseHandler);
}

// ==========================
// Command Handlers
// ==========================

void helpHandler(cmd* c) {
  Serial.println("\nAvailable Commands:");
  Serial.println("  help          - Displays this help message");
  Serial.println("  version       - Displays application version");
  Serial.println("  set <key> <value> - Set a value for a specific setting or password");
  Serial.println("  get <key>     - Retrieve the value of a specific setting or password");
  Serial.println("  list          - List all stored settings and passwords");
  Serial.println("  erase         - Erase all stored settings");
  Serial.println("\nAvailable Keys:");
  Serial.println("  WifiSSID, WifiPass, MqttBroker, MqttPort, MqttTopic, MqttUser, MqttPass");
  Serial.println("  Password1 - Password10");
}

void versionHandler(cmd* c) {
  Serial.printf("\nApplication Version: %s\n", VERSION);
}

void setHandler(cmd* c) {
  Command cmd(c);
  if (cmd.countArgs() < 2) {
    Serial.println("\nError: Missing arguments. Usage: set <key> <value>");
    return;
  }

  String key = cmd.getArgument(0).getValue();
  String value = cmd.getArgument(1).getValue();

  preferences.putString(key.c_str(), value);
  Serial.printf("\n%s set to: %s\n", key.c_str(), value.c_str());
}

void getHandler(cmd* c) {
  Command cmd(c);
  if (cmd.countArgs() < 1) {
    Serial.println("\nError: Missing argument. Usage: get <key>");
    return;
  }

  String key = cmd.getArgument(0).getValue();
  String value = preferences.getString(key.c_str(), "");

  if (value == "") {
    Serial.printf("\nNo value found for key: %s\n", key.c_str());
  } else {
    Serial.printf("\n%s: %s\n", key.c_str(), value.c_str());
  }
}

void listHandler(cmd* c) {
  Serial.println("\nStored Settings and Passwords:");
  printPreferences();
}

void eraseHandler(cmd* c) {
  preferences.clear();
  Serial.println("\nAll settings erased.");
}

// ==========================
// Helper Functions
// ==========================

void handleCommand(String input) {
  input.trim();
  if (input.length() > 0) {
    cli.parse(input);
    if (cli.errored()) {
      CommandError e = cli.getError();
      Serial.printf("\nError: %s\n", e.toString().c_str());
    }
  }
}

void printPreferences() {
  const char* keys[] = {"WifiSSID", "WifiPass", "MqttBroker", "MqttPort", "MqttTopic", 
                        "MqttUser", "MqttPass", "Password1", "Password2", "Password3", 
                        "Password4", "Password5", "Password6", "Password7", "Password8", 
                        "Password9", "Password10"};

  for (const char* key : keys) {
    String value = preferences.getString(key, "");
    if (value != "") {
      Serial.printf("%s: %s\n", key, value.c_str());
    } else {
      Serial.printf("%s: [not set]\n", key);
    }
  }
}
