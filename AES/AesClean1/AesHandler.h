/*
 * AesHandler.h
 *
 *  Created on: December 16, 2024
 *      Author: Matthew Elgert
 */

#ifndef AES_HANDLER_H_
#define AES_HANDLER_H_

#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include "mbedtls/pkcs5.h"
#include "arduino_base64.hpp"
#include <Arduino.h>
#include <vector>

/**
 * @class AesHandler
 * @brief A class that provides AES-256 CBC encryption and decryption functionality.
 * 
 * This class securely encrypts and decrypts strings using AES-256 CBC mode.
 * It uses a salt, PBKDF2 key derivation, and PKCS#7 padding for secure encryption.
 * Requires base64_encode and tested on version 2.0.4 - https://github.com/dojyorin/arduino_base64
 * Verified working on ESP32 Arduino Core v2.0.17 - https://github.com/espressif/arduino-esp32/tree/2.0.17
 * Testing works with PassTxt.Shared/Helpers/AesHelper.cs
 */
class AesHandler {
public:
    /**
     * @brief Constructor initializes encryption settings.
     * - Salt size: 16 bytes.
     * - Key size: 256 bits (32 bytes).
     * - AES block size: 16 bytes.
     * - PBKDF2 iterations: 10,000.
     */
    AesHandler() : saltSize(16), iterations(10000), keySize(32), blockSize(16) {}

    /**
     * @brief Encrypts a plain text string with a password.
     * @param plainText The string to encrypt.
     * @param password The password used for encryption.
     * @return The encrypted string, base64-encoded.
     */
    String encrypt(const String &plainText, const String &password) {
        // Generate random salt and derive key/IV from the password.
        std::vector<uint8_t> salt = generateRandomBytes(saltSize);
        std::vector<uint8_t> key(keySize), iv(blockSize);
        deriveKeyAndIV(password.c_str(), salt.data(), key.data(), iv.data());

        // Calculate padded length and prepare input buffer.
        size_t paddedLen = getPaddedLength(plainText.length(), blockSize);
        std::vector<uint8_t> inputBuffer(paddedLen);
        memcpy(inputBuffer.data(), plainText.c_str(), plainText.length());
        applyPKCS7Padding(inputBuffer.data(), plainText.length(), blockSize);

        // Encrypt data.
        std::vector<uint8_t> cipherText(paddedLen);
        encryptData(inputBuffer.data(), paddedLen, key.data(), iv.data(), cipherText.data());

        // Combine salt and ciphertext.
        std::vector<uint8_t> saltedCipherText(saltSize + paddedLen);
        memcpy(saltedCipherText.data(), salt.data(), saltSize);
        memcpy(saltedCipherText.data() + saltSize, cipherText.data(), paddedLen);

        // Base64 encode the combined result.
        std::vector<char> encodedText(base64::encodeLength(saltedCipherText.size()));
        base64::encode(saltedCipherText.data(), saltedCipherText.size(), encodedText.data());
        return String(encodedText.data());
    }

    /**
     * @brief Decrypts an encrypted, base64-encoded string using a password.
     * @param cipherText The base64-encoded encrypted string.
     * @param password The password used for decryption.
     * @return The decrypted plain text string.
     */
    String decrypt(const String &cipherText, const String &password) {
        // Decode base64 input.
        std::vector<uint8_t> decodedBytes(base64::decodeLength(cipherText.c_str()));
        base64::decode(cipherText.c_str(), decodedBytes.data());

        // Extract salt and derive key/IV.
        std::vector<uint8_t> salt(saltSize);
        memcpy(salt.data(), decodedBytes.data(), saltSize);
        std::vector<uint8_t> key(keySize), iv(blockSize);
        deriveKeyAndIV(password.c_str(), salt.data(), key.data(), iv.data());

        // Extract ciphertext data.
        uint8_t *cipherData = decodedBytes.data() + saltSize;
        size_t cipherLen = decodedBytes.size() - saltSize;

        // Decrypt data.
        std::vector<uint8_t> plainTextBuffer(cipherLen);
        decryptData(cipherData, cipherLen, key.data(), iv.data(), plainTextBuffer.data());

        // Remove PKCS#7 padding and return the result.
        size_t plainTextLen = removePKCS7Padding(plainTextBuffer.data(), cipherLen);
        return String(reinterpret_cast<const char *>(plainTextBuffer.data()), plainTextLen);
    }

private:
    const size_t saltSize;    ///< Size of the salt in bytes.
    const size_t iterations;  ///< Number of iterations for PBKDF2.
    const size_t keySize;     ///< Size of the encryption key in bytes.
    const size_t blockSize;   ///< AES block size in bytes.

    /**
     * @brief Generates a buffer of random bytes.
     * @param length Number of random bytes to generate.
     * @return A vector containing the random bytes.
     */
    std::vector<uint8_t> generateRandomBytes(size_t length) {
        std::vector<uint8_t> buffer(length);
        for (size_t i = 0; i < length; ++i) {
            buffer[i] = random(0, 256);
        }
        return buffer;
    }

    /**
     * @brief Calculates the padded length for PKCS#7 padding.
     * @param inputLen The original input length.
     * @param blockSize The block size for padding.
     * @return The padded length.
     */
    size_t getPaddedLength(size_t inputLen, size_t blockSize) {
        return ((inputLen / blockSize) + 1) * blockSize;
    }

    /**
     * @brief Applies PKCS#7 padding to a buffer.
     * @param buffer The buffer to pad.
     * @param inputLen The original input length.
     * @param blockSize The block size for padding.
     */
    void applyPKCS7Padding(uint8_t *buffer, size_t inputLen, size_t blockSize) {
        uint8_t padding = blockSize - (inputLen % blockSize);
        memset(buffer + inputLen, padding, padding);
    }

    /**
     * @brief Removes PKCS#7 padding from a buffer.
     * @param buffer The buffer containing padded data.
     * @param length The length of the padded data.
     * @return The length of the data without padding.
     */
    size_t removePKCS7Padding(const uint8_t *buffer, size_t length) {
        return length - buffer[length - 1];
    }

    /**
     * @brief Derives the encryption key and IV using PBKDF2.
     * @param password The password used for key derivation.
     * @param salt The salt value.
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
     * @brief Encrypts data using AES-256 CBC mode.
     * @param plainText Input plain text data.
     * @param length Length of the input data.
     * @param key Encryption key.
     * @param iv Initialization vector.
     * @param output Output buffer for the encrypted data.
     */
    void encryptData(const uint8_t *plainText, size_t length, const uint8_t *key, const uint8_t *iv, uint8_t *output) {
        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_enc(&aes, key, keySize * 8);
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, length, const_cast<uint8_t *>(iv), plainText, output);
        mbedtls_aes_free(&aes);
    }

    /**
     * @brief Decrypts data using AES-256 CBC mode.
     * @param cipherText Input encrypted data.
     * @param length Length of the encrypted data.
     * @param key Decryption key.
     * @param iv Initialization vector.
     * @param output Output buffer for the decrypted data.
     */
    void decryptData(const uint8_t *cipherText, size_t length, const uint8_t *key, const uint8_t *iv, uint8_t *output) {
        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_dec(&aes, key, keySize * 8);
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, length, const_cast<uint8_t *>(iv), cipherText, output);
        mbedtls_aes_free(&aes);
    }
};

#endif /* AES_HANDLER_H_ */
