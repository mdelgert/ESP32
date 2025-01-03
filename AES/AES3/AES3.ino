#include <Arduino.h>
#include "AESCrypto.h"

// ######################## Warning not working with complex password need to fix ########################
// Global variables
const String password = "mysecretpassword"; // Encryption password
const String plaintext = "This is AES CBC test."; // Text to encrypt and decrypt

AESCrypto aes; // AESCrypto object

void setup()
{
    // Initialize Serial for debugging
    Serial.begin(115200);
    while (!Serial)
        ; // Wait for the serial connection to establish

    // Initial log message
    Serial.println("Starting AES CBC encryption and decryption...");
}

void loop()
{
    // Encrypt the plaintext
    String encrypted = aes.encrypt(password, plaintext);
    Serial.println("Encrypted Base64: " + encrypted);

    // Decrypt the encrypted text
    String decrypted = aes.decrypt(password, encrypted);
    Serial.println("Decrypted text: " + decrypted);

    // Wait before the next iteration
    delay(1000);
}
