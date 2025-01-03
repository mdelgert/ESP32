#include <aes/esp_aes.h>
#include "mbedtls/md.h"
#include "mbedtls/pkcs5.h"

#define KEY_SIZE 32  // 256-bit key (32 bytes)
#define BLOCK_SIZE 16 // 128-bit block (16 bytes)
#define SALT_SIZE 16
#define ITERATIONS 10000

// Buffers for salt, key, and IV
uint8_t salt[SALT_SIZE];
uint8_t key[KEY_SIZE];
uint8_t iv[BLOCK_SIZE];

// Generate random bytes for salt
void generateRandomBytes(uint8_t* buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[i] = random(0, 256);
    }
}

// Derive AES key and IV using PBKDF2
void deriveKeyAndIV(const char* password, const uint8_t* salt, size_t saltSize, uint8_t* key, uint8_t* iv) {
    mbedtls_md_context_t sha256_ctx;
    mbedtls_md_init(&sha256_ctx);

    const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    mbedtls_md_setup(&sha256_ctx, md_info, 1);

    // Derive key and IV using PBKDF2
    mbedtls_pkcs5_pbkdf2_hmac(&sha256_ctx,
                              (const unsigned char*)password, strlen(password),
                              salt, saltSize,
                              ITERATIONS,
                              KEY_SIZE + BLOCK_SIZE,
                              key);

    // Split the derived key into AES key and IV
    memcpy(iv, key + KEY_SIZE, BLOCK_SIZE);
    mbedtls_md_free(&sha256_ctx);
}

// AES encryption
void aesEncrypt(const uint8_t* plainText, uint8_t* cipherText) {
    esp_aes_context aes_ctx;
    esp_aes_init(&aes_ctx);

    // Set encryption key
    esp_aes_setkey(&aes_ctx, key, 256);

    // Encrypt one block
    esp_aes_crypt_ecb(&aes_ctx, ESP_AES_ENCRYPT, plainText, cipherText);

    esp_aes_free(&aes_ctx);
}

// AES decryption
void aesDecrypt(const uint8_t* cipherText, uint8_t* decryptedText) {
    esp_aes_context aes_ctx;
    esp_aes_init(&aes_ctx);

    // Set decryption key
    esp_aes_setkey(&aes_ctx, key, 256);

    // Decrypt one block
    esp_aes_crypt_ecb(&aes_ctx, ESP_AES_DECRYPT, cipherText, decryptedText);

    esp_aes_free(&aes_ctx);
}

// Helper function to print data as hex
void printHex(const char* label, const uint8_t* data, size_t length) {
    Serial.print(label);
    for (size_t i = 0; i < length; i++) {
        if (i > 0 && i % 16 == 0) Serial.println();
        Serial.printf("%02X ", data[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    randomSeed(analogRead(0)); // Initialize random seed
}

void loop() {
    // Define password and plaintext
    const char* password = "securepassword123";
    const char* plainText = "Hello, AES World!"; // Exactly 16 characters
    uint8_t plainTextBuffer[BLOCK_SIZE] = {0};  // No null terminator needed for encryption
    uint8_t cipherTextBuffer[BLOCK_SIZE] = {0};
    uint8_t decryptedTextBuffer[BLOCK_SIZE + 1] = {0};  // Extra byte for null terminator

    // Copy plaintext into buffer (no null terminator added here)
    strncpy((char*)plainTextBuffer, plainText, BLOCK_SIZE);

    // Generate salt and derive key/IV
    generateRandomBytes(salt, SALT_SIZE);
    deriveKeyAndIV(password, salt, SALT_SIZE, key, iv);

    // Encrypt plaintext
    aesEncrypt(plainTextBuffer, cipherTextBuffer);

    // Decrypt ciphertext
    aesDecrypt(cipherTextBuffer, decryptedTextBuffer);

    // Add null terminator after decryption
    decryptedTextBuffer[BLOCK_SIZE] = '\0'; // Ensure null termination for printing

    // Print results
    printHex("Salt: ", salt, SALT_SIZE);
    printHex("Key: ", key, KEY_SIZE);
    printHex("IV: ", iv, BLOCK_SIZE);
    printHex("Plaintext: ", plainTextBuffer, BLOCK_SIZE);
    printHex("Ciphertext: ", cipherTextBuffer, BLOCK_SIZE);
    printHex("Decrypted Text: ", decryptedTextBuffer, BLOCK_SIZE);
    Serial.print("Decrypted Text (String): ");
    Serial.println((char*)decryptedTextBuffer);

    // Wait 1 second
    delay(1000);
}
