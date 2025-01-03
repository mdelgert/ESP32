#include "duckparser.h"
#include "keyboard.h"
#include "USB.h"

// Pre-defined DuckScript commands to demonstrate the HID keyboard functionality
const char* demoCommands[] = {
    "STRING Hello, this is a demo!",
    "DELAY 1000",
    "STRING Testing special keys:",
    "DELAY 500",
    "ENTER",
    "STRING Pressing Arrow Keys...",
    "DELAY 500",
    "UPARROW",
    "DOWNARROW",
    "LEFTARROW",
    "RIGHTARROW",
    "DELAY 1000",
    "STRING Goodbye!",
    "ENTER",
};

const int numCommands = sizeof(demoCommands) / sizeof(demoCommands[0]);

void setup() {
    // Initialize the HID Keyboard
    Serial.begin(115200);
    Serial.println("Starting HID Keyboard Demo...");
    duckparser::beginKeyboard();
    USB.begin();
    delay(200);
}

void loop() {
    Serial.println("Running hardcoded commands...");
    
    // Loop through the pre-defined DuckScript commands
    for (int i = 0; i < numCommands; i++) {
        Serial.print("Executing: ");
        Serial.println(demoCommands[i]);
        
        // Call the duckparser with each hardcoded command
        duckparser::parse(demoCommands[i], strlen(demoCommands[i]));
        
        delay(100); // Short delay between commands for demonstration
    }
    
    Serial.println("Demo complete. Restarting in 5 seconds...");
    delay(5000);  // Pause before restarting the loop
}
