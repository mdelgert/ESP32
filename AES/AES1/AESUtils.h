// AESUtils.h
#ifndef AES_UTILS_H
#define AES_UTILS_H

#include <mbedtls/aes.h>
#include <Arduino.h>

class AESUtils {
public:
    static String encrypt(const String &text, const String &password) {
        unsigned char key[16];
        unsigned char iv[16];
        unsigned char encrypted[32];
        size_t text_len = text.length();
        size_t padded_len = ((text_len + 15) / 16) * 16;

        memset(key, 0, sizeof(key));
        memset(iv, 0, sizeof(iv));
        memcpy(key, password.c_str(), min(password.length(), sizeof(key)));
        memcpy(iv, password.c_str(), min(password.length(), sizeof(iv)));

        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_enc(&aes, key, 128);
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, padded_len, iv, (unsigned char *)text.c_str(), encrypted);
        mbedtls_aes_free(&aes);

        String encryptedHex = "";
        for (size_t i = 0; i < padded_len; i++) {
            char hex[3];
            sprintf(hex, "%02X", encrypted[i]);
            encryptedHex += hex;
        }

        return encryptedHex;
    }

    static String decrypt(const String &encryptedHex, const String &password) {
        unsigned char key[16];
        unsigned char iv[16];
        unsigned char encrypted[32];
        unsigned char decrypted[32];
        size_t encrypted_len = encryptedHex.length() / 2;

        memset(key, 0, sizeof(key));
        memset(iv, 0, sizeof(iv));
        memcpy(key, password.c_str(), min(password.length(), sizeof(key)));
        memcpy(iv, password.c_str(), min(password.length(), sizeof(iv)));

        for (size_t i = 0; i < encrypted_len; i++) {
            sscanf(encryptedHex.substring(i * 2, i * 2 + 2).c_str(), "%02X", &encrypted[i]);
        }

        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_dec(&aes, key, 128);
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, encrypted_len, iv, encrypted, decrypted);
        mbedtls_aes_free(&aes);

        decrypted[encrypted_len] = '\0';
        return String((char *)decrypted);
    }
};

#endif
