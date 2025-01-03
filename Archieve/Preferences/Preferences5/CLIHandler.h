#ifndef CLI_HANDLER_H
#define CLI_HANDLER_H

#include <SimpleCLI.h>
#include "PreferencesHandler.h"

class CLIHandler {
private:
    SimpleCLI cli;

    Command setCmd, getCmd, removeCmd, eraseCmd, helpCmd, clearCmd;

    static const char* VERSION;

public:
    static CLIHandler& getInstance() {
        static CLIHandler instance;
        return instance;
    }

    void init() {
        setupCommands();
        Serial.println("\nESP32-S3 CLI Ready. Type 'help' for a list of commands.");
    }

    void update() {
        if (Serial.available()) {
            String input = Serial.readStringUntil('\n');
            handleCommand(input);
        }
    }

private:
    void setupCommands() {
        setCmd = cli.addCmd("set", setHandler);
        setCmd.addPositionalArgument("key");
        setCmd.addPositionalArgument("value");

        getCmd = cli.addCmd("get", getHandler);
        getCmd.addPositionalArgument("key");

        removeCmd = cli.addCmd("remove", removeHandler);
        removeCmd.addPositionalArgument("key");

        eraseCmd = cli.addCmd("erase", eraseHandler);
        helpCmd = cli.addCmd("help", helpHandler);
        clearCmd = cli.addCmd("clear", clearHandler);
    }

    void handleCommand(String input) {
        input.trim();
        if (input.length() > 0) {
            cli.parse(input);
            if (cli.errored()) {
                CommandError e = cli.getError();
                Serial.printf("Error: %s\n", e.toString().c_str());
            }
        }
    }

    // Static Command Handlers
    static void helpHandler(cmd* c);
    static void setHandler(cmd* c);
    static void getHandler(cmd* c);
    static void eraseHandler(cmd* c);
    static void removeHandler(cmd* c);
    static void clearHandler(cmd* c);
};

const char* CLIHandler::VERSION = "1.0.1";

// Command Implementations
void CLIHandler::helpHandler(cmd* c) {
    Serial.println("\nAvailable Commands:");
    Serial.println("  set <key> <value>   - Save a key-value pair.");
    Serial.println("                        Example: set WifiSSID MyNetwork");
    Serial.println("                                 set Password1 secret123");
    Serial.println("  get <key>           - Retrieve the value of a key.");
    Serial.println("                        Example: get WifiSSID");
    Serial.println("  remove <key>        - Remove a specific key.");
    Serial.println("                        Example: remove WifiSSID");
    Serial.println("  erase               - Clear all stored keys and values.");
    Serial.println("                        Example: erase");
    Serial.println("  clear               - Clear the terminal screen.");
    Serial.println("  help                - Show this help message with examples.");
    Serial.println("\nTips:");
    Serial.println("  - Keys are case-sensitive.");
    Serial.println("  - Use unique keys like WifiSSID, Password1, etc.");
    Serial.println("  - Make sure to confirm stored values with 'get <key>'.");
}

void CLIHandler::setHandler(cmd* c) {
    Command cmd(c);
    String key = cmd.getArgument("key").getValue();
    String value = cmd.getArgument("value").getValue();

    PreferencesHandler::getInstance().setValue(key, value);
    Serial.printf("Key '%s' set to '%s'\n", key.c_str(), value.c_str());
}

void CLIHandler::getHandler(cmd* c) {
    Command cmd(c);
    String key = cmd.getArgument("key").getValue();

    String value;
    if (PreferencesHandler::getInstance().getValue(key, value)) {
        Serial.printf("Key '%s': %s\n", key.c_str(), value.c_str());
    } else {
        Serial.printf("Key '%s' not found.\n", key.c_str());
    }
}

void CLIHandler::eraseHandler(cmd* c) {
    PreferencesHandler::getInstance().clear();
    Serial.println("All stored preferences have been erased.");
}

void CLIHandler::removeHandler(cmd* c) {
    Command cmd(c);
    String key = cmd.getArgument("key").getValue();

    if (PreferencesHandler::getInstance().removeValue(key)) {
        Serial.printf("Key '%s' removed.\n", key.c_str());
    } else {
        Serial.printf("Key '%s' not found.\n", key.c_str());
    }
}

void CLIHandler::clearHandler(cmd* c) {
    Serial.print("\033[2J\033[H");
    for (int i = 0; i < 50; i++) {
        Serial.println();
    }
    //Serial.println("Terminal cleared.");
}

#endif // CLI_HANDLER_H
