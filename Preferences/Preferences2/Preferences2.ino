#include <Preferences.h>
#include <SimpleCLI.h>

// Global instances
Preferences preferences;
SimpleCLI cli;

// Secret Key Placeholder
String secret1 = "";

// Command declarations
Command setSecretCmd, getCmd, eraseCmd, helpCmd;

// Function Prototypes
void setupCommands();
void setSecretCallback(cmd *c);
void getCallback(cmd *c);
void eraseCallback(cmd *c);
void helpCallback(cmd *c);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // Initialize Preferences
  preferences.begin("app", false); // "app" is the namespace, false means read/write mode.

  // Load existing secret
  secret1 = preferences.getString("secret1", "");

  // Initialize CLI Commands
  setupCommands();

  Serial.println("Welcome! Type 'help' for available commands.");
}

void loop()
{

  //Serial.println("Test");
  //delay(1000);

  // CLI Input Handler
  while (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    cli.parse(input);
  }
}

// Initialize CLI Commands
void setupCommands()
{
  // Set Secret Command
  setSecretCmd = cli.addCmd("set", setSecretCallback);
  setSecretCmd.addPositionalArgument("key", "secret1");
  setSecretCmd.addPositionalArgument("value");

  // Get Settings Command
  getCmd = cli.addCmd("get", getCallback);

  // Erase Settings Command
  eraseCmd = cli.addCmd("erase", eraseCallback);

  // Help Command
  helpCmd = cli.addCmd("help", helpCallback);
}

// Set Secret Callback
void setSecretCallback(cmd *c)
{
  Command cmd(c);
  String key = cmd.getArgument("key").getValue();
  String value = cmd.getArgument("value").getValue();

  if (key == "secret1")
  {
    preferences.putString("secret1", value);
    secret1 = value;
    Serial.println("Secret1 updated successfully!");
  }
  else
  {
    Serial.println("Error: Unsupported key. Use 'secret1'.");
  }
}

// Get Settings Callback
void getCallback(cmd *c)
{
  if (secret1 != "")
  {
    Serial.print("Secret1: ");
    Serial.println(secret1);
  }
  else
  {
    Serial.println("No secret is set yet.");
  }
}

// Erase Settings Callback
void eraseCallback(cmd *c)
{
  preferences.clear();
  secret1 = "";
  Serial.println("All settings erased successfully.");
}

// Help Callback
void helpCallback(cmd *c)
{
  Serial.println("Available Commands:");
  Serial.println("  set secret1 <value> - Set a secret value.");
  Serial.println("  get                - Retrieve the current secret.");
  Serial.println("  erase              - Erase all saved settings.");
  Serial.println("  help               - Show this help message.");
}
