#include <Arduino.h>
#include "AesEspHandler.h"

// Create a Cipher object
AesEspHandler *cipher = new AesEspHandler();

void setup()
{
    Serial.begin(115200);
    delay(1000); // Give Serial Monitor time to initialize
}

void loop()
{
    String password = "FikWMHb0e5BMyauEop5fA1y9/TIurttHV+F7VXZcaon1jOt3J";
    String plainText = "AesClean2 Working!...";

    // Encrypt
    String encryptedText = cipher->encrypt(plainText, password);

    //String encryptedText = "mauluwuS+wDrk3SMt75bKb+KyJ1v2Yh894mlvUkGJH0=";
    Serial.println("\nEncrypted Text (Base64):");
    Serial.println(encryptedText);

    // Decrypt
     String decryptedText = cipher->decrypt(encryptedText, password);

    Serial.println("\nDecrypted Text:");
    Serial.println(decryptedText);

    // Wait for 1 second before repeating
    //delay(1000);
}
