### Links
https://www.youtube.com/watch?v=WKkCGsj198s
https://medium.com/@bhautik.markeye/esp32-aes-encryption-using-esp-idf-for-a-string-of-any-length-85fc46ad0d73

### Crossplatform Encryption
To implement encryption that works across **Blazor WebAssembly**, **MAUI Hybrid**, and **Arduino ESP32**, you need a solution that:

1. Supports **WebAssembly's sandboxed environment**.
2. Leverages **.NET's full cryptography APIs** for MAUI.
3. Is compatible with **embedded systems like the ESP32**, which often use libraries written in C.

### **Recommended Approach**
The best approach is to use **AES encryption** with a shared encryption library or algorithm. AES is widely supported across platforms, efficient, and secure. Below is a detailed plan for encryption that works across all these environments.

---

### **1. Encryption Standard: AES-256**
- **Why AES?**
  - AES is a symmetric encryption algorithm (same key for encryption and decryption).
  - Supported by all major platforms, including browsers (via Web Cryptography API), .NET, and embedded devices.
  - Efficient for small devices like ESP32.
- **Key Length**: Use 256-bit keys (32 bytes) for strong security.

---

### **2. Blazor WebAssembly**
Blazor WebAssembly doesn't support native .NET cryptography libraries like `Aes.Create()`, but you can use the **Web Cryptography API** through JavaScript interop for AES encryption.

#### **Example Code**:
1. **JavaScript (wwwroot/js/crypto.js)**:
   ```javascript
   async function encryptAES(key, iv, data) {
       const encodedKey = await crypto.subtle.importKey(
           "raw",
           key,
           { name: "AES-CBC" },
           false,
           ["encrypt"]
       );
       const encodedData = new TextEncoder().encode(data);
       const encrypted = await crypto.subtle.encrypt(
           { name: "AES-CBC", iv: iv },
           encodedKey,
           encodedData
       );
       return Array.from(new Uint8Array(encrypted));
   }

   async function decryptAES(key, iv, encryptedData) {
       const encodedKey = await crypto.subtle.importKey(
           "raw",
           key,
           { name: "AES-CBC" },
           false,
           ["decrypt"]
       );
       const decrypted = await crypto.subtle.decrypt(
           { name: "AES-CBC", iv: iv },
           encodedKey,
           new Uint8Array(encryptedData)
       );
       return new TextDecoder().decode(decrypted);
   }
   ```

2. **C# Interop**:
   ```csharp
   public async Task<List<byte>> EncryptAsync(string key, string iv, string data)
   {
       var encrypted = await JSRuntime.InvokeAsync<List<byte>>(
           "encryptAES", Convert.FromBase64String(key), Convert.FromBase64String(iv), data
       );
       return encrypted;
   }

   public async Task<string> DecryptAsync(string key, string iv, List<byte> encryptedData)
   {
       var decrypted = await JSRuntime.InvokeAsync<string>(
           "decryptAES", Convert.FromBase64String(key), Convert.FromBase64String(iv), encryptedData
       );
       return decrypted;
   }
   ```

---

### **3. Blazor MAUI Hybrid**
Blazor MAUI Hybrid apps run in a native environment, so you can use the full .NET **System.Security.Cryptography** library to handle AES encryption.

#### **Example Code**:
```csharp
public byte[] EncryptAES(string plainText, byte[] key, byte[] iv)
{
    using var aes = Aes.Create();
    aes.Key = key;
    aes.IV = iv;

    using var encryptor = aes.CreateEncryptor();
    using var ms = new MemoryStream();
    using var cs = new CryptoStream(ms, encryptor, CryptoStreamMode.Write);
    using var writer = new StreamWriter(cs);
    writer.Write(plainText);
    writer.Close();

    return ms.ToArray();
}

public string DecryptAES(byte[] encryptedData, byte[] key, byte[] iv)
{
    using var aes = Aes.Create();
    aes.Key = key;
    aes.IV = iv;

    using var decryptor = aes.CreateDecryptor();
    using var ms = new MemoryStream(encryptedData);
    using var cs = new CryptoStream(ms, decryptor, CryptoStreamMode.Read);
    using var reader = new StreamReader(cs);

    return reader.ReadToEnd();
}
```

---

### **4. Arduino ESP32**
For the ESP32, you can use the **AES implementation provided by Arduino libraries**, such as **Arduino Cryptography Library (Crypto)** or **MbedTLS** (built into the ESP32 SDK).

#### **Example Code**:
1. **Install Library**:
   - Use the `AESLib` library or the native `mbedtls` library included with the ESP32 framework.

2. **Encryption with AESLib**:
   ```cpp
   #include <AESLib.h>

   AES aes;

   void encryptAES(const char* plainText, const char* key, const char* iv, byte* encryptedData) {
       aes.do_aes_encrypt(
           (byte*)plainText, strlen(plainText),
           encryptedData,
           (byte*)key, 256,
           (byte*)iv
       );
   }

   void decryptAES(const byte* encryptedData, const char* key, const char* iv, char* decryptedText) {
       aes.do_aes_decrypt(
           encryptedData, 32, // 32 bytes block size
           (byte*)decryptedText,
           (byte*)key, 256,
           (byte*)iv
       );
   }
   ```

---

### **5. Key Exchange**
Because you are working across multiple platforms, you'll need a secure way to exchange or synchronize encryption keys:
- Use a **pre-shared key (PSK)** stored securely on each device.
- Implement **Diffie-Hellman key exchange** for dynamic key negotiation (requires server support).
- Consider **RSA encryption** to securely exchange AES keys.

---

### **Summary**

| Platform         | Library/API Used                   | Notes                                                                                  |
|-------------------|------------------------------------|----------------------------------------------------------------------------------------|
| **Blazor WASM**   | Web Cryptography API via Interop  | Use JavaScript interop for AES encryption (browser-based).                             |
| **Blazor MAUI**   | System.Security.Cryptography      | Full .NET cryptographic APIs (AES, RSA, HMAC).                                         |
| **Arduino ESP32** | AESLib or MbedTLS                 | Lightweight and efficient AES encryption for embedded systems.                         |

By standardizing on **AES-256** for encryption and using platform-appropriate libraries, you can achieve compatibility across all these environments. Ensure proper key management and IV synchronization to maintain security and interoperability.