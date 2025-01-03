#include <Arduino.h>
#include "AESUtils.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("\nESP32-S3 AES Utility Example");
}

void loop()
{
  // Example usage
  String text = "Hello, ESP32-S3 AES!";
  String password = "mysecretpassword";

  Serial.println("Original Text:");
  Serial.println(text);

  // Encrypt the text
  String encrypted = AESUtils::encrypt(text, password);
  Serial.println("Encrypted Text:");
  Serial.println(encrypted);

  // Decrypt the text
  String decrypted = AESUtils::decrypt(encrypted, password);
  Serial.println("Decrypted Text:");
  Serial.println(decrypted);
  delay(1000);
}