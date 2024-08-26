//https://www.reddit.com/r/esp32/comments/114j40i/help_serial_monitor_not_working_with_a_new_esp32/
//In Arduino IDE go to tools "USB CDC on Boot Enabled"
//First time may require unplug from USB and plug back in to work

void setup() {
  Serial.begin(115200);  // Initialize Serial communication at 115200 baud rate
  delay(1000);           // Small delay to ensure the serial connection is ready
  //Serial.println("Hello, ESP32-S3!");  // Print a message to the Serial Monitor
}

void loop() {
  Serial.println("Hello, ESP32-S3!");
  delay(1000);  // Delay for a second between loop iterations
}

