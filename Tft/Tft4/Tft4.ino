// DOES NOT WORK
//arduino-cli lib search "bb_spi_lcd"
//arduino-cli lib install "bb_spi_lcd"@2.7.1

#include <bb_spi_lcd.h>

// Define pin configuration
#define TFT_CS_PIN  4   // Chip Select
#define TFT_SDA_PIN 3   // MOSI
#define TFT_SCL_PIN 5   // SCLK
#define TFT_DC_PIN  2   // Data/Command
#define TFT_RES_PIN 1   // Reset
#define TFT_BL_PIN  38  // Backlight

// Create LCD object
bb_spi_lcd lcd;

void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);
  Serial.println("Initializing LCD...");

  // Set backlight pin and turn it on
  pinMode(TFT_BL_PIN, OUTPUT);
  digitalWrite(TFT_BL_PIN, LOW); // Turn on backlight

  // Initialize LCD
  lcd.begin(TFT_SCL_PIN, TFT_SDA_PIN, TFT_CS_PIN, TFT_DC_PIN, TFT_RES_PIN);
  lcd.setRotation(1); // Set orientation
  lcd.clear(BLACK);   // Clear screen with black background

  // Display text
  lcd.setColor(WHITE);
  lcd.setFontSize(2);
  lcd.print("Hello", 10, 30); // Print "Hello" at x=10, y=30
}

void loop() {
  // No loop logic needed for static text
}

