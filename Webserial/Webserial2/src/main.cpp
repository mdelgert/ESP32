#include <Arduino.h>
#include "improv.h"

using namespace improv;

// Buffer for receiving serial data
constexpr size_t BUFFER_SIZE = 256;
uint8_t buffer[BUFFER_SIZE];
size_t buffer_pos = 0;

// Function to handle parsed Improv commands
bool handleCommand(ImprovCommand command) {
  Serial.println("Received Improv Command");
  if (command.command == WIFI_SETTINGS) {
    Serial.printf("SSID: %s\n", command.ssid.c_str());
    Serial.printf("Password: %s\n", command.password.c_str());
    
    // Here, you could add logic to connect to the Wi-Fi network
    Serial.println("Attempting Wi-Fi connection...");
    // Wi-Fi connection code here

    return true;
  }

  Serial.println("Unknown command received");
  return false;
}

// Function to handle errors
void handleError(Error error) {
  Serial.printf("Error: %d\n", error);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Improv Wi-Fi Example");
}

void loop() {
  // Read incoming serial data
  while (Serial.available() > 0) {
    uint8_t byte = Serial.read();
    if (buffer_pos < BUFFER_SIZE) {
      buffer[buffer_pos++] = byte;

      // Process each byte using the Improv SDK
      if (!parse_improv_serial_byte(buffer_pos - 1, byte, buffer, handleCommand, handleError)) {
        Serial.println("Invalid data, resetting buffer.");
        buffer_pos = 0;  // Reset buffer on error
      }
    } else {
      Serial.println("Buffer overflow, resetting.");
      buffer_pos = 0;  // Reset buffer if it overflows
    }
  }
}

