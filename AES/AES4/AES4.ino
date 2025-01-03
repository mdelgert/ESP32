#include "aes/esp_aes.h"

// Function to print data as a human-readable hex string
void printHex(const char *label, const uint8_t *data, size_t length)
{
    Serial.print(label);
    for (size_t i = 0; i < length; i++)
    {
        if (i > 0 && i % 16 == 0)
            Serial.println();            // Line break every 16 bytes
        Serial.printf("%02X ", data[i]); // Print byte in hexadecimal format
    }
    Serial.println();
}

// Function to print data as a human-readable string
void printString(const char *label, const uint8_t *data, size_t length)
{
    Serial.print(label);
    for (size_t i = 0; i < length; i++)
    {
        Serial.print((char)data[i]); // Convert bytes to characters
    }
    Serial.println();
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
}

void loop()
{
    // Example AES key (128-bit / 16 bytes)
    const uint8_t key[16] = {
        0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0xCF, 0x39, 0x9B, 0x31, 0x5D, 0x03};

    // Example plaintext (human-readable string, padded to 16 bytes)
    const char *plaintextString = "Hello, AES World!";
    uint8_t plaintext[16] = {0};
    strncpy((char *)plaintext, plaintextString, sizeof(plaintext));

    uint8_t ciphertext[16] = {0};    // Buffer for ciphertext
    uint8_t decryptedtext[16] = {0}; // Buffer for decrypted text

    esp_aes_context ctx;

    // Initialize AES context and set encryption key
    esp_aes_init(&ctx);
    esp_aes_setkey(&ctx, key, 128); // 128-bit key

    // Encrypt the plaintext
    esp_aes_crypt_ecb(&ctx, ESP_AES_ENCRYPT, plaintext, ciphertext);

    // Display plaintext and ciphertext
    printString("Plaintext (String): ", plaintext, sizeof(plaintext));
    printHex("Ciphertext (Hex): ", ciphertext, sizeof(ciphertext));

    // Decrypt the ciphertext
    esp_aes_crypt_ecb(&ctx, ESP_AES_DECRYPT, ciphertext, decryptedtext);

    // Display decrypted text
    printHex("Decrypted Text (Hex): ", decryptedtext, sizeof(decryptedtext));
    printString("Decrypted Text (String): ", decryptedtext, sizeof(decryptedtext));

    // Clean up AES context
    esp_aes_free(&ctx);
    delay(1000);
}
