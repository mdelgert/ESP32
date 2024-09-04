#include <PNGdec.h>
#include "ImageKey.h" 
#include "ImageWifi.h"
#include "SPI.h"
#include <TFT_eSPI.h>   // Hardware-specific library

PNG png; // PNG decoder instance
TFT_eSPI tft = TFT_eSPI(); // TFT instance

#define MAX_IMAGE_WIDTH 160 // Image width
#define IMAGE_COUNT 2       // Number of images to rotate through

// Store image data and sizes in arrays for easy rotation
const uint8_t* images[] = {ImageKey, ImageWifi}; // Add more images here if needed
const size_t imageSizes[] = {sizeof(ImageKey), sizeof(ImageWifi)}; 

int currentImageIndex = 0;  // Start with the first image
unsigned long lastImageSwitch = 0;  // Track time for image switching

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  drawImage();  // Draw the initial image

  tft.setCursor(20, 30);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.println("Start");
}

void loop() {
  // Rotate to the next image every second
  if (millis() - lastImageSwitch > 1000) {
    currentImageIndex = (currentImageIndex + 1) % IMAGE_COUNT;  // Switch image
    drawImage();  // Draw the new image
    lastImageSwitch = millis();  // Reset the timer
  }

  delay(3000); 
}

// Reusable function to draw the current image
void drawImage() {
  tft.fillScreen(TFT_BLACK); // Clear the screen
  int16_t rc = png.openFLASH((uint8_t*)images[currentImageIndex], imageSizes[currentImageIndex], pngDraw);  // Cast to non-const
  if (rc == PNG_SUCCESS) {
    tft.startWrite();
    png.decode(NULL, 0);  // Decode and draw the image
    tft.endWrite();
  }
}

// Draw callback function for PNGdec
void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(0, pDraw->y, pDraw->iWidth, 1, lineBuffer);
}
