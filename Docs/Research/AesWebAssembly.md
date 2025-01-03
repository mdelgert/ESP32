To simplify the solution, we’ll leave your `AesHelper` class unchanged for platforms where AES is supported and use JavaScript’s Web Crypto API only for WebAssembly (Blazor WebAssembly). This approach avoids modifying your existing encryption/decryption logic while ensuring compatibility with the WebAssembly runtime.

### Steps to Use JavaScript Web Crypto for WebAssembly

#### Step 1: Add JavaScript Functions
Create a new JavaScript file (e.g., `aesHelper.js`) in your `wwwroot` folder with the following Web Crypto API implementation:

```javascript
window.aesHelper = {
    encrypt: async (plainText, password) => {
        const enc = new TextEncoder();
        const keyMaterial = await crypto.subtle.importKey(
            "raw",
            enc.encode(password),
            "PBKDF2",
            false,
            ["deriveKey"]
        );

        const key = await crypto.subtle.deriveKey(
            {
                name: "PBKDF2",
                salt: enc.encode("salt"),
                iterations: 10000,
                hash: "SHA-256",
            },
            keyMaterial,
            { name: "AES-GCM", length: 256 },
            false,
            ["encrypt"]
        );

        const iv = crypto.getRandomValues(new Uint8Array(12));
        const cipherText = await crypto.subtle.encrypt(
            { name: "AES-GCM", iv },
            key,
            enc.encode(plainText)
        );

        return btoa(String.fromCharCode(...iv) + String.fromCharCode(...new Uint8Array(cipherText)));
    },

    decrypt: async (encryptedText, password) => {
        const enc = new TextEncoder();
        const keyMaterial = await crypto.subtle.importKey(
            "raw",
            enc.encode(password),
            "PBKDF2",
            false,
            ["deriveKey"]
        );

        const key = await crypto.subtle.deriveKey(
            {
                name: "PBKDF2",
                salt: enc.encode("salt"),
                iterations: 10000,
                hash: "SHA-256",
            },
            keyMaterial,
            { name: "AES-GCM", length: 256 },
            false,
            ["decrypt"]
        );

        const data = atob(encryptedText);
        const iv = new Uint8Array([...data].slice(0, 12).map(c => c.charCodeAt(0)));
        const cipherText = new Uint8Array([...data].slice(12).map(c => c.charCodeAt(0)));

        const plainText = await crypto.subtle.decrypt(
            { name: "AES-GCM", iv },
            key,
            cipherText
        );

        return new TextDecoder().decode(plainText);
    }
};
```

Add this script reference in your `index.html` (or `_Host.cshtml` for Blazor Server):

```html
<script src="aesHelper.js"></script>
```

#### Step 2: Create JavaScript Interop Methods in C#
Add a `AesHelperInterop` class to handle calls to JavaScript.

```csharp
using Microsoft.JSInterop;
using System.Threading.Tasks;

namespace PassTxt.Shared.Helpers
{
    public static class AesHelperInterop
    {
        public static async Task<string> EncryptAsync(IJSRuntime jsRuntime, string plainText, string password)
        {
            return await jsRuntime.InvokeAsync<string>("aesHelper.encrypt", plainText, password);
        }

        public static async Task<string> DecryptAsync(IJSRuntime jsRuntime, string encryptedText, string password)
        {
            return await jsRuntime.InvokeAsync<string>("aesHelper.decrypt", encryptedText, password);
        }
    }
}
```

#### Step 3: Update the Razor Page
Modify your Blazor page to use `AesHelperInterop` when running in WebAssembly.

```razor
@inject IJSRuntime JSRuntime

<div class="d-grid gap-2 mb-3">
    <button class="btn btn-primary" @onclick="EncryptTextAsync">Encrypt</button>
</div>
<div class="d-grid gap-2 mb-3">
    <button class="btn btn-success" @onclick="DecryptTextAsync">Decrypt</button>
</div>

@code {
    private async Task EncryptTextAsync()
    {
        try
        {
            if (OperatingSystem.IsBrowser()) // WebAssembly
            {
                EncryptedText = await AesHelperInterop.EncryptAsync(JSRuntime, PlainText, Password);
            }
            else
            {
                EncryptedText = AesHelper.Encrypt(PlainText, Password);
            }
            DecryptedText = string.Empty;
        }
        catch (Exception ex)
        {
            EncryptedText = $"Error: {ex.Message}";
        }
    }

    private async Task DecryptTextAsync()
    {
        try
        {
            if (OperatingSystem.IsBrowser()) // WebAssembly
            {
                DecryptedText = await AesHelperInterop.DecryptAsync(JSRuntime, EncryptedText, Password);
            }
            else
            {
                DecryptedText = AesHelper.Decrypt(EncryptedText, Password);
            }
        }
        catch (Exception ex)
        {
            DecryptedText = $"Error: {ex.Message}";
        }
    }
}
```

### Summary of Changes
1. **JavaScript Web Crypto API**:
   - Implemented in `aesHelper.js`.
2. **JavaScript Interop**:
   - Added `AesHelperInterop` for calling JavaScript methods from Blazor.
3. **Conditional Logic**:
   - Used `OperatingSystem.IsBrowser()` to decide whether to use JavaScript or native `AesHelper`.

### Advantages
- **No Third-Party Libraries**: Leverages the Web Crypto API built into browsers.
- **Minimal Code Changes**: Only adds a small interop layer for WebAssembly.
- **Cross-Platform Consistency**: Ensures that encrypted and decrypted strings work consistently across platforms.

This approach keeps your codebase simple while maintaining compatibility with both native and WebAssembly environments.