/*
 * AesHandler.h
 *
 *  Created on: December 16, 2024
 *      Author: Matthew Elgert
 */

#ifndef AES_ESP_HANDLER_H_
#define AES_ESP_HANDLER_H_

#include <aes/esp_aes.h>
#include "mbedtls/md.h"
#include "mbedtls/pkcs5.h"
#include "arduino_base64.hpp"
#include <Arduino.h>
#include <vector>

/**
 * @class AesEspHandler
 * @brief Handles AES encryption and decryption using ESP32 hardware acceleration.
 * 
 * This class provides methods for AES-256 CBC encryption and decryption, with support for
 * key derivation using PBKDF2-HMAC-SHA256, PKCS#7 padding, and base64 encoding/decoding.
 * Requires base64_encode and tested on version 2.0.4 - https://github.com/dojyorin/arduino_base64
 * Verified working on ESP32 Arduino Core v2.0.17 - https://github.com/espressif/arduino-esp32/tree/2.0.17
 * Testing works with PassTxt.Shared/Helpers/AesHelper.cs
 */
class AesEspHandler {
public:
    /**
     * @brief Constructor initializes encryption parameters.
     * 
     * - Salt size: 16 bytes
     * - Key size: 256 bits (32 bytes)
     * - AES block size: 16 bytes
     * - PBKDF2 iterations: 5000
     */
    AesEspHandler() : saltSize(16), iterations(5000), keySize(32), blockSize(16) {}

    /**
     * @brief Encrypts a plain text string using a password.
     * 
     * The encryption process:
     * 1. Generate a random salt.
     * 2. Derive a key and IV from the password and salt using PBKDF2-HMAC-SHA256.
     * 3. Apply PKCS#7 padding to the plain text.
     * 4. Encrypt the padded text using AES-256-CBC.
     * 5. Prepend the salt to the cipher text.
     * 6. Encode the result using Base64.
     * 
     * @param plainText The plain text to encrypt.
     * @param password The password for key derivation.
     * @return Encrypted string encoded in Base64.
     */
    String encrypt(const String &plainText, const String &password) {
        std::vector<uint8_t> salt = generateRandomBytes(saltSize);
        std::vector<uint8_t> key(keySize), iv(blockSize);
        deriveKeyAndIV(password.c_str(), salt.data(), key.data(), iv.data());

        size_t paddedLen = getPaddedLength(plainText.length(), blockSize);
        std::vector<uint8_t> inputBuffer(paddedLen);
        memcpy(inputBuffer.data(), plainText.c_str(), plainText.length());
        applyPKCS7Padding(inputBuffer.data(), plainText.length(), blockSize);

        std::vector<uint8_t> cipherText(paddedLen);
        encryptData(inputBuffer.data(), paddedLen, key.data(), iv.data(), cipherText.data());

        std::vector<uint8_t> saltedCipherText;
        saltedCipherText.reserve(saltSize + paddedLen);
        saltedCipherText.insert(saltedCipherText.end(), salt.begin(), salt.end());
        saltedCipherText.insert(saltedCipherText.end(), cipherText.begin(), cipherText.end());

        std::vector<char> encodedText(base64::encodeLength(saltedCipherText.size()));
        base64::encode(saltedCipherText.data(), saltedCipherText.size(), encodedText.data());
        return String(encodedText.data());
    }

    /**
     * @brief Decrypts an encrypted Base64-encoded string using a password.
     * 
     * The decryption process:
     * 1. Decode the input from Base64.
     * 2. Extract the salt and derive the key and IV using PBKDF2-HMAC-SHA256.
     * 3. Decrypt the cipher text using AES-256-CBC.
     * 4. Remove PKCS#7 padding to recover the original plain text.
     * 
     * @param cipherText The encrypted Base64-encoded string.
     * @param password The password for key derivation.
     * @return The decrypted plain text.
     */
    String decrypt(const String &cipherText, const String &password) {
        std::vector<uint8_t> decodedBytes(base64::decodeLength(cipherText.c_str()));
        base64::decode(cipherText.c_str(), decodedBytes.data());

        std::vector<uint8_t> salt(saltSize);
        memcpy(salt.data(), decodedBytes.data(), saltSize);
        std::vector<uint8_t> key(keySize), iv(blockSize);
        deriveKeyAndIV(password.c_str(), salt.data(), key.data(), iv.data());

        uint8_t *cipherData = decodedBytes.data() + saltSize;
        size_t cipherLen = decodedBytes.size() - saltSize;

        std::vector<uint8_t> plainTextBuffer(cipherLen);
        decryptData(cipherData, cipherLen, key.data(), iv.data(), plainTextBuffer.data());

        size_t plainTextLen = removePKCS7Padding(plainTextBuffer.data(), cipherLen);
        return String(reinterpret_cast<const char *>(plainTextBuffer.data()), plainTextLen);
    }

private:
    const size_t saltSize;    ///< Salt size in bytes.
    const size_t iterations;  ///< Number of PBKDF2 iterations.
    const size_t keySize;     ///< AES key size in bytes.
    const size_t blockSize;   ///< AES block size in bytes.

    /**
     * @brief Generates a vector of random bytes using the ESP32 hardware RNG.
     * 
     * @param length Number of random bytes to generate.
     * @return A vector containing random bytes.
     */
    std::vector<uint8_t> generateRandomBytes(size_t length) {
        std::vector<uint8_t> buffer(length);
        uint32_t randValue;
        for (size_t i = 0; i < length; i += 4) {
            randValue = esp_random();
            memcpy(buffer.data() + i, &randValue, (length - i < 4) ? length - i : 4);
        }
        return buffer;
    }

    /**
     * @brief Calculates the padded length for PKCS#7 padding.
     * 
     * @param inputLen Length of the input data.
     * @param blockSize AES block size.
     * @return The length of the padded data.
     */
    size_t getPaddedLength(size_t inputLen, size_t blockSize) {
        return ((inputLen / blockSize) + 1) * blockSize;
    }

    /**
     * @brief Applies PKCS#7 padding to the input buffer.
     * 
     * @param buffer Input buffer to apply padding.
     * @param inputLen Length of the input data.
     * @param blockSize AES block size.
     */
    void applyPKCS7Padding(uint8_t *buffer, size_t inputLen, size_t blockSize) {
        uint8_t padding = blockSize - (inputLen % blockSize);
        memset(buffer + inputLen, padding, blockSize - (inputLen % blockSize));
    }

    /**
     * @brief Removes PKCS#7 padding from the decrypted buffer.
     * 
     * @param buffer Buffer containing padded data.
     * @param length Length of the buffer.
     * @return Length of the data after removing padding.
     */
    size_t removePKCS7Padding(const uint8_t *buffer, size_t length) {
        return length - buffer[length - 1];
    }

    /**
     * @brief Derives the encryption key and IV using PBKDF2-HMAC-SHA256.
     * 
     * @param password Password used for key derivation.
     * @param salt Salt value.
     * @param key Output buffer for the derived key.
     * @param iv Output buffer for the derived IV.
     */
    void deriveKeyAndIV(const char *password, const uint8_t *salt, uint8_t *key, uint8_t *iv) {
        mbedtls_md_context_t ctx;
        mbedtls_md_init(&ctx);
        const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
        mbedtls_md_setup(&ctx, md_info, 1);

        std::vector<uint8_t> keyIV(keySize + blockSize);
        mbedtls_pkcs5_pbkdf2_hmac(&ctx, reinterpret_cast<const uint8_t *>(password), strlen(password),
                                  salt, saltSize, iterations, keyIV.size(), keyIV.data());
        memcpy(key, keyIV.data(), keySize);
        memcpy(iv, keyIV.data() + keySize, blockSize);
        mbedtls_md_free(&ctx);
    }

    /**
     * @brief Encrypts data using AES-256-CBC mode.
     * 
     * @param plainText Input plain text buffer.
     * @param length Length of the input data.
     * @param key AES encryption key.
     * @param iv Initialization vector.
     * @param output Output buffer for encrypted data.
     */
    void encryptData(const uint8_t *plainText, size_t length, const uint8_t *key, const uint8_t *iv, uint8_t *output) {
        esp_aes_context aes;
        esp_aes_init(&aes);
        esp_aes_setkey(&aes, key, keySize * 8);
        esp_aes_crypt_cbc(&aes, ESP_AES_ENCRYPT, length, const_cast<uint8_t *>(iv), plainText, output);
        esp_aes_free(&aes);
    }

    /**
     * @brief Decrypts data using AES-256-CBC mode.
     * 
     * @param cipherText Input cipher text buffer.
     * @param length Length of the input data.
     * @param key AES decryption key.
     * @param iv Initialization vector.
     * @param output Output buffer for decrypted data.
     */
    void decryptData(const uint8_t *cipherText, size_t length, const uint8_t *key, const uint8_t *iv, uint8_t *output) {
        esp_aes_context aes;
        esp_aes_init(&aes);
        esp_aes_setkey(&aes, key, keySize * 8);
        esp_aes_crypt_cbc(&aes, ESP_AES_DECRYPT, length, const_cast<uint8_t *>(iv), cipherText, output);
        esp_aes_free(&aes);
    }
};

#endif /* AES_ESP_HANDLER_H_ */
