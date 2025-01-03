#ifndef AESCRYPTO_H
#define AESCRYPTO_H

#include <mbedtls/aes.h>
#include <mbedtls/md5.h>
#include <Arduino.h>

// AES configuration
#define AES_KEY_SIZE 16 // 128 bits (derived from MD5)
#define AES_BLOCK_SIZE 16 // 128 bits

class AESCrypto {
public:
    // Generate AES key from password using MD5
    void generateKey(const String &password, unsigned char *key) const {
        mbedtls_md5_context md5;
        mbedtls_md5_init(&md5);
        mbedtls_md5_starts_ret(&md5);
        mbedtls_md5_update_ret(&md5, (const unsigned char *)password.c_str(), password.length());
        mbedtls_md5_finish_ret(&md5, key);
        mbedtls_md5_free(&md5);
    }

    // Generate random IV
    void generateRandomIV(unsigned char *iv, size_t len) const {
        for (size_t i = 0; i < len; i++) {
            iv[i] = random(0, 256); // Generate random byte
        }
    }

    // Add PKCS#7 padding
    size_t addPadding(unsigned char *buffer, size_t len) const {
        size_t paddingLen = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
        for (size_t i = 0; i < paddingLen; i++) {
            buffer[len + i] = paddingLen;
        }
        return len + paddingLen;
    }

    // Remove PKCS#7 padding
    size_t removePadding(unsigned char *buffer, size_t len) const {
        size_t paddingLen = buffer[len - 1];
        return len - paddingLen;
    }

    // Base64 encode
    String base64Encode(const unsigned char *data, size_t len) const {
        static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        String encoded = "";
        for (size_t i = 0; i < len; i += 3) {
            uint32_t n = (data[i] << 16) | ((i + 1 < len ? data[i + 1] : 0) << 8) | (i + 2 < len ? data[i + 2] : 0);
            encoded += table[(n >> 18) & 63];
            encoded += table[(n >> 12) & 63];
            encoded += (i + 1 < len) ? table[(n >> 6) & 63] : '=';
            encoded += (i + 2 < len) ? table[n & 63] : '=';
        }
        return encoded;
    }

    // Base64 decode
    size_t base64Decode(const String &input, unsigned char *output) const {
        static const int8_t table[256] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,  0, -1, -1,
            -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
            -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
        };
        size_t output_len = 0;
        uint32_t buffer = 0;
        int bits_collected = 0;

        for (size_t i = 0; i < input.length(); i++) {
            int8_t value = table[(uint8_t)input[i]];
            if (value == -1) continue;
            buffer = (buffer << 6) | value;
            bits_collected += 6;
            if (bits_collected >= 8) {
                bits_collected -= 8;
                output[output_len++] = (buffer >> bits_collected) & 0xFF;
            }
        }
        return output_len;
    }

    // Encrypt plaintext using password
    String encrypt(const String &password, const String &plaintext) const {
        unsigned char key[AES_KEY_SIZE];
        generateKey(password, key);

        size_t plaintext_len = plaintext.length();
        size_t padded_len = plaintext_len + AES_BLOCK_SIZE;
        unsigned char *paddedPlaintext = new unsigned char[padded_len];
        memcpy(paddedPlaintext, plaintext.c_str(), plaintext_len);
        padded_len = addPadding(paddedPlaintext, plaintext_len);

        unsigned char iv[AES_BLOCK_SIZE];
        generateRandomIV(iv, AES_BLOCK_SIZE);

        size_t encrypted_len = padded_len + AES_BLOCK_SIZE;
        unsigned char *encrypted = new unsigned char[encrypted_len];
        memcpy(encrypted, iv, AES_BLOCK_SIZE); // Prepend IV to output buffer

        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_enc(&aes, key, AES_KEY_SIZE * 8); // Key size in bits
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, padded_len, iv, paddedPlaintext, encrypted + AES_BLOCK_SIZE);
        mbedtls_aes_free(&aes);

        String result = base64Encode(encrypted, encrypted_len);

        delete[] paddedPlaintext;
        delete[] encrypted;
        return result;
    }

    // Decrypt ciphertext using password
    String decrypt(const String &password, const String &encryptedBase64) const {
        unsigned char key[AES_KEY_SIZE];
        generateKey(password, key);

        size_t decoded_len = encryptedBase64.length() * 3 / 4 + 1;
        unsigned char *decoded = new unsigned char[decoded_len];
        decoded_len = base64Decode(encryptedBase64, decoded);

        unsigned char iv[AES_BLOCK_SIZE];
        memcpy(iv, decoded, AES_BLOCK_SIZE);

        size_t ciphertext_len = decoded_len - AES_BLOCK_SIZE;
        unsigned char *decrypted = new unsigned char[ciphertext_len];

        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_dec(&aes, key, AES_KEY_SIZE * 8); // Key size in bits
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, ciphertext_len, iv, decoded + AES_BLOCK_SIZE, decrypted);
        mbedtls_aes_free(&aes);

        size_t plaintext_len = removePadding(decrypted, ciphertext_len);
        String result = String((char *)decrypted).substring(0, plaintext_len);

        delete[] decoded;
        delete[] decrypted;
        return result;
    }
};

#endif // AESCRYPTO_H
