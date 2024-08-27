# Steps to Convert Using Image2CPP
Go to Image2CPP.
Upload your image.
Set the dimensions (e.g., 160x80).
Set the output format to "Arduino Code" and color mode to "RGB565".
Click on "Generate" to get the C array code.
Copy the generated C array.

https://javl.github.io/image2cpp/

const uint16_t myImage[12800] = {
  0xFFFF, 0xFFFF, ... // The array data goes here
};

# Todo this would require some tunning etc....