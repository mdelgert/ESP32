#include <Arduino.h>
#include "Cipher.h"

// Create a Cipher object
Cipher *cipher = new Cipher();

void setup()
{
    Serial.begin(115200);
    delay(1000); // Give Serial Monitor time to initialize
}

void loop()
{
    //String password = "securepassword123";
    //String password = "password";
    //String password = "FikWMHb0e5BMyauEop5fA1y9/TIurttHV+F7VXZcaon1jOt3JidBd2ZDyeEJbqyGlY2UMXb3blR83nhsyDra/rCtDEf6yxxNzvVsTCOzFVc=";
    String password = "FikWMHb0e5BMyauEop5fA1y9/TIurttHV+F7VXZcaon1jOt3J";
    String plainText = "AES encryption example using Base64 object. Working!";

    //Serial.println("Original Plaintext:");
    //Serial.println(plainText);

    // Encrypt
    String encryptedText = cipher->encryptString(plainText, password);
    //String encryptedText = "mauluwuS+wDrk3SMt75bKb+KyJ1v2Yh894mlvUkGJH0=";
    Serial.println("\nEncrypted Text (Base64):");
    Serial.println(encryptedText);

    // Decrypt
    String decryptedText = cipher->decryptString(encryptedText, password);
    Serial.println("\nDecrypted Text:");
    Serial.println(decryptedText);

    // Wait for 1 second before repeating
    //delay(1000);
}
