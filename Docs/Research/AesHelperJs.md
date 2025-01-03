Using **UTF-8 encoding** for the password is **not a security issue**. It's a standard and widely used encoding for text data across platforms, ensuring consistency. Here's why you needed to explicitly set it:

---

### Why UTF-8 Was Necessary

1. **C# Defaults to UTF-16**:
   - In the original C# implementation, the `Rfc2898DeriveBytes` class implicitly used **UTF-16** encoding for the password because .NET strings are UTF-16 by default.
   - JavaScript's `TextEncoder` uses **UTF-8** by default, which caused a mismatch in key derivation.

2. **Explicit UTF-8 in C# Fixes the Mismatch**:
   - By explicitly encoding the password as **UTF-8** in C#, we aligned the behavior of C# and JavaScript.
   - Both platforms now process the password consistently, ensuring that the derived `Key` and `IV` match.

---

### Why JavaScript Didn't Work Previously

The earlier JavaScript implementation used **UTF-16 encoding (`utf-16le`)** for the password (via `TextEncoder`), attempting to match the default behavior of `Rfc2898DeriveBytes`. However:
1. **Inconsistency in Encoding**:
   - The C# implementation hadn't explicitly set UTF-16; it relied on implicit behavior.
   - This led to unpredictable behavior between platforms when the encoding logic was changed.

2. **UTF-16 in JavaScript Wasn't the Default**:
   - JavaScript's `TextEncoder` defaults to UTF-8. Switching to `utf-16le` introduced an unnecessary complexity, and the mismatch persisted due to other parameter issues (e.g., Base64 handling or password processing).

---

### Why UTF-8 Is Better and Safe

1. **Interoperability**:
   - UTF-8 is the standard text encoding used across web technologies and APIs.
   - Using UTF-8 ensures consistency across systems, especially between JavaScript and .NET.

2. **No Security Impact**:
   - The encoding of the password doesn’t weaken the security of the PBKDF2 function, as long as the same encoding is used consistently.
   - PBKDF2's strength lies in its hashing and key derivation process, not the specific encoding of the input.

3. **Simplicity**:
   - Aligning both platforms to use UTF-8 avoids reliance on platform-specific defaults and ensures predictable behavior.

---

### Lessons Learned

1. **Always Explicitly Specify Encoding**:
   - Default behaviors can differ between platforms and languages. Explicitly specifying encoding avoids surprises.

2. **Match Key Derivation Parameters**:
   - Key derivation (PBKDF2) is sensitive to even small mismatches, such as encoding or salt size.

3. **Stick to UTF-8 for Interoperability**:
   - UTF-8 is the de facto standard for cross-platform communication. Aligning both platforms to UTF-8 makes your implementation more robust and portable.

---

### Conclusion

The root issue was the mismatch in password encoding between C# and JavaScript. Switching both to **UTF-8** fixed the problem and ensures a secure, interoperable solution. There's no security risk in using UTF-8, and it simplifies future integrations. 
