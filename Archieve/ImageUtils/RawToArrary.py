import struct

# Read the raw image file
with open("image.raw", "rb") as f:
    data = f.read()

# Convert to 16-bit (2-byte) RGB565 format and output as a C array
with open("image.h", "w") as f:
    f.write("const uint16_t gImage_logo[] = {\n")
    
    for i in range(0, len(data), 2):
        # Convert two bytes at a time
        pixel = struct.unpack('H', data[i:i+2])[0]
        f.write(f"0x{pixel:04X}, ")
        
        # Add a newline every 16 values for readability
        if i % 32 == 30:
            f.write("\n")

    f.write("};\n")

