//Working with 
// arduino-cli core install esp32:esp32@3.0.7
// arduino-cli lib install "Adafruit GFX Library"@1.11.11
// arduino-cli lib install "Adafruit ST7735 and ST7789 Library"@1.10.4

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Define your pins
#define TFT_CS    4   // Chip Select
#define TFT_RST   1   // Reset
#define TFT_DC    2   // Data/Command
#define TFT_MOSI  3   // MOSI (SDA)
#define TFT_SCLK  5   // Clock (SCL)
#define TFT_BL    38  // Backlight

// Initialize the ST7735 display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing display...");

  // Backlight control
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Turn on backlight

  // Initialize the display
  tft.initR(INITR_MINI160x80); // Initialize for 160x80 resolution
  tft.setRotation(3);         // Set rotation: 0, 1, 2, or 3

  // Fill the screen with black
  tft.fillScreen(ST77XX_BLACK);

  // Test drawing
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("Hello, ESP32-S3!");

  tft.fillRect(10, 30, 60, 30, ST77XX_RED); // Draw a red rectangle
}

void loop() {
  //Example: Blink the backlight
  digitalWrite(TFT_BL, LOW);
  delay(500);
  digitalWrite(TFT_BL, HIGH);
  delay(500);
}
