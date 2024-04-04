#include <EEPROM.h>

// Define the maximum length for each value
const int MAX_LENGTH = 32;

// EEPROM addresses for each value
const int DEVICE_NAME_ADDR = 0;
const int SSID_ADDR = DEVICE_NAME_ADDR + MAX_LENGTH;
const int PASSWORD_ADDR = SSID_ADDR + MAX_LENGTH;

// Declare global variables
char deviceName[MAX_LENGTH];
char ssid[MAX_LENGTH];
char password[MAX_LENGTH];

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Welcome! Type '1' to set values or '2' to retrieve values.");
  retrieveValues();
}

void loop() {
  if (Serial.available()) {
    char choice = Serial.read();
    switch (choice) {
      case '1':
        setValues();
        break;
      case '2':
        retrieveValues();
        break;
      default:
        Serial.println("Invalid choice. Type '1' to set values or '2' to retrieve values.");
    }
  }
}

void clearSerialBuffer() {
  while (Serial.available()) {
    Serial.read(); // Read and discard characters from the buffer
  }
}

void readInput(char* buffer, int maxLength) {
  int index = 0;
  while (index < maxLength) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n') {
        buffer[index] = '\0'; // Null-terminate the string
        break;
      }
      buffer[index] = c;
      index++;
    }
  }
}



void setValues() {
  
  clearSerialBuffer();

  // Prompt user for input
  Serial.println("Enter the following values:");
  Serial.print("Device Name: ");
  readInput(deviceName, MAX_LENGTH);
  Serial.print("SSID: ");
  readInput(ssid, MAX_LENGTH);
  Serial.print("Password: ");
  readInput(password, MAX_LENGTH);

  // Save values to EEPROM
  EEPROM.put(DEVICE_NAME_ADDR, deviceName);
  EEPROM.put(SSID_ADDR, ssid);
  EEPROM.put(PASSWORD_ADDR, password);

  // Show the values
  retrieveValues();
  
}

void retrieveValues() {

  clearSerialBuffer();
  
  // Retrieve saved values from EEPROM
  EEPROM.get(DEVICE_NAME_ADDR, deviceName);
  EEPROM.get(SSID_ADDR, ssid);
  EEPROM.get(PASSWORD_ADDR, password);

  // Print retrieved values
  Serial.println("\nRetrieved values:");
  Serial.print("Device Name: ");
  Serial.println(deviceName);
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
}
