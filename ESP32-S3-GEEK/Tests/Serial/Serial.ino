#include "USB.h"

void setup() {
  USB.begin();            // Initialize USB for Serial communication
  delay(1000);            // Small delay to ensure the serial connection is ready

  Serial.begin(115200);   // Start Serial communication over USB
  while (!Serial) {       // Wait for Serial to be available
    delay(10);
  }

  Serial.println("Hello, ESP32-S3!");
}

void loop() {
  Serial.println("Hello, ESP32-S3!");
  delay(1000);
}
