#include <Preferences.h>
#include <SimpleCLI.h>
#include <ArduinoJson.h>

// Global instances
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

void setup() {
  Serial.begin(115200);

  // Start Preferences namespace
  preferences.begin("app", false); // "app" is the namespace.

  // Initialize CLI Commands
  setupCommands();

  Serial.println("Welcome! Use 'help' for available commands.");
}

void loop() {
  // Process CLI input
  while (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    cli.parse(input);
  }
}

// Setup all CLI commands
void setupCommands() {
  // Set Command
  setCmd = cli.addCmd("set", setCallback);
  setCmd.addPositionalArgument("key");
  setCmd.addPositionalArgument("value");

  // Get Command
  getCmd = cli.addCmd("get", getCallback);
  getCmd.addPositionalArgument("key");

  // Erase Command
  eraseCmd = cli.addCmd("erase", eraseCallback);
  eraseCmd.addPositionalArgument("key", "");

  // List Command
  listCmd = cli.addCmd("list", listCallback);

  // Help Command
  helpCmd = cli.addCmd("help", helpCallback);
}

// Generic Set Key-Value Pair
void setCallback(cmd* c) {
  Command cmd(c);
  String key = cmd.getArgument("key").getValue();
  String value = cmd.getArgument("value").getValue();

  preferences.putString(key.c_str(), value);
  Serial.print("Saved: ");
  Serial.print(key);
  Serial.print(" = ");
  Serial.println(value);
}

// Generic Get Key-Value Pair
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

// Erase a Specific Key or All Keys
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

// List All Keys and Values (JSON Format)
void listCallback(cmd* c) {
  Serial.println("Saved Keys and Values:");
  StaticJsonDocument<512> jsonDoc;

  // Manually iterate through keys (limited simulation as Preferences has no iterator)
  for (int i = 0; i < 10; i++) { // Simulating up to 10 saved keys
    String key = "password" + String(i + 1);
    String value = preferences.getString(key.c_str(), "");
    if (value != "") {
      jsonDoc[key] = value;
    }
  }

  // Print as JSON
  String output;
  serializeJson(jsonDoc, output);
  Serial.println(output);
}

// Display Help
void helpCallback(cmd* c) {
  Serial.println("Available Commands:");
  Serial.println("  set <key> <value>   - Save a key-value pair.");
  Serial.println("  get <key>           - Retrieve the value of a key.");
  Serial.println("  erase [key]         - Erase a specific key or all keys if none specified.");
  Serial.println("  list                - List all saved keys and values.");
  Serial.println("  help                - Show this help message.");
}
