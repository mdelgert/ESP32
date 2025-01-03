#ifndef CIPHER_H_
#define CIPHER_H_

#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include "mbedtls/pkcs5.h"
#include "arduino_base64.hpp"
#include <Arduino.h>

class Cipher {
public:
    Cipher() {
        saltSize = 16;      // Matches SaltSize in C#
        iterations = 10000; // Matches Iterations in C#
        keySize = 32;       // 256-bit key
        blockSize = 16;     // AES block size
    }

    String encryptString(const String &plainText, const String &password) {
        uint8_t salt[saltSize];
        generateRandomBytes(salt, saltSize);

        uint8_t key[keySize];
        uint8_t iv[blockSize];
        deriveKeyAndIV(password.c_str(), salt, key, iv);

        size_t inputLen = plainText.length();
        size_t paddedLen = getPaddedLength(inputLen, blockSize);

        uint8_t inputBuffer[paddedLen];
        memset(inputBuffer, 0, paddedLen);
        memcpy(inputBuffer, plainText.c_str(), inputLen);
        applyPKCS7Padding(inputBuffer, inputLen, blockSize);

        uint8_t cipherText[paddedLen];
        encrypt(inputBuffer, paddedLen, key, iv, cipherText);

        size_t saltedLen = saltSize + paddedLen;
        uint8_t saltedCipherText[saltedLen];
        memcpy(saltedCipherText, salt, saltSize);
        memcpy(saltedCipherText + saltSize, cipherText, paddedLen);

        size_t encodedLen = base64::encodeLength(saltedLen);
        char encodedText[encodedLen];
        base64::encode(saltedCipherText, saltedLen, encodedText);

        return String(encodedText);
    }

    String decryptString(const String &cipherText, const String &password) {
        size_t decodedLen = base64::decodeLength(cipherText.c_str());
        uint8_t decodedBytes[decodedLen];
        base64::decode(cipherText.c_str(), decodedBytes);

        uint8_t salt[saltSize];
        memcpy(salt, decodedBytes, saltSize);

        uint8_t key[keySize];
        uint8_t iv[blockSize];
        deriveKeyAndIV(password.c_str(), salt, key, iv);

        uint8_t *cipherTextData = decodedBytes + saltSize;
        size_t cipherTextLen = decodedLen - saltSize;

        uint8_t plainTextBuffer[cipherTextLen];
        decrypt(cipherTextData, cipherTextLen, key, iv, plainTextBuffer);

        size_t plainTextLen = removePKCS7Padding(plainTextBuffer, cipherTextLen);
        char plainText[plainTextLen + 1];
        memcpy(plainText, plainTextBuffer, plainTextLen);
        plainText[plainTextLen] = '\0';

        return String(plainText);
    }

private:
    size_t saltSize;
    size_t iterations;
    size_t keySize;
    size_t blockSize;

    void generateRandomBytes(uint8_t *buffer, size_t length) {
        for (size_t i = 0; i < length; i++) {
            buffer[i] = random(0, 256);
        }
    }

    size_t getPaddedLength(size_t inputLen, size_t blockSize) {
        return ((inputLen / blockSize) + 1) * blockSize;
    }

    void applyPKCS7Padding(uint8_t *buffer, size_t inputLen, size_t blockSize) {
        uint8_t padding = blockSize - (inputLen % blockSize);
        for (size_t i = inputLen; i < inputLen + padding; i++) {
            buffer[i] = padding;
        }
    }

    size_t removePKCS7Padding(uint8_t *buffer, size_t length) {
        uint8_t padding = buffer[length - 1];
        return length - padding;
    }

    void deriveKeyAndIV(const char *password, const uint8_t *salt, uint8_t *key, uint8_t *iv) {
        mbedtls_md_context_t sha256_ctx;
        mbedtls_md_init(&sha256_ctx);
        const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
        mbedtls_md_setup(&sha256_ctx, md_info, 1);

        uint8_t keyIV[keySize + blockSize];
        mbedtls_pkcs5_pbkdf2_hmac(&sha256_ctx, (const unsigned char *)password, strlen(password),
                                  salt, saltSize, iterations, keySize + blockSize, keyIV);
        memcpy(key, keyIV, keySize);
        memcpy(iv, keyIV + keySize, blockSize);

        mbedtls_md_free(&sha256_ctx);
    }

    void encrypt(const uint8_t *plainText, size_t length, const uint8_t *key, const uint8_t *iv, uint8_t *output) {
        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_enc(&aes, key, keySize * 8);
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, length, (unsigned char *)iv, plainText, output);
        mbedtls_aes_free(&aes);
    }

    void decrypt(const uint8_t *cipherText, size_t length, const uint8_t *key, const uint8_t *iv, uint8_t *output) {
        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_dec(&aes, key, keySize * 8);
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, length, (unsigned char *)iv, cipherText, output);
        mbedtls_aes_free(&aes);
    }
};

#endif /* CIPHER_H_ */
