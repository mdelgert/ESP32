
// This example renders a png file that is stored in a FLASH array
// using the PNGdec library (available via library manager).

// Image files can be converted to arrays using the tool here:
// https://notisrac.github.io/FileToCArray/
// To use this tool:
//   1. Drag and drop file on "Browse..." button
//   2. Tick box "Treat as binary"
//   3. Click "Convert"
//   4. Click "Save as file" and move the header file to sketch folder
//   5. Open the sketch in IDE
//   6. Include the header file containing the array (panda.h in this example)

// Include the PNG decoder library
#include <PNGdec.h>
//#include "ImageKey.h" // Image is stored here in an 8 bit array
#include "ImageWifi.h" // Image is stored here in an 8 bit array

PNG png; // PNG decoder inatance

//#define MAX_IMAGE_WDITH 240 // Adjust for your images
#define MAX_IMAGE_WDITH 160 // Adjust for your images

int16_t xpos = 0;
int16_t ypos = 0;

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

void setup()
{
  // Initialise the TFT
  tft.begin();
  tft.setRotation(3); // Set rotation to flip the screen
  tft.fillScreen(TFT_BLACK);
  //tft.fillScreen(TFT_WHITE);

  //Draw png image
  //int16_t rc = png.openFLASH((uint8_t *)ImageKey, sizeof(ImageKey), pngDraw);
  int16_t rc = png.openFLASH((uint8_t *)ImageWifi, sizeof(ImageWifi), pngDraw);

  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    uint32_t dt = millis();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
  
  //tft.setCursor(0, 0);
  tft.setCursor(20, 30);
  //tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color to white and background to black
  tft.setTextColor(TFT_WHITE);  // Only set the text color, no background color so its transparent
  tft.setTextSize(2); // Set text size to 2x the default size
  tft.println("WIFI!");

}

void loop()
{
  //Do stuff here
}

void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WDITH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}
