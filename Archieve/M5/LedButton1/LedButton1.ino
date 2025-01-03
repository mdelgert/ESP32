#define FASTLED_INTERNAL // remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#include "M5Atom.h"

// Function to cycle through the colors
void cycleColors()
{
  // Set display to RED
  M5.dis.fillpix(0xFF0000); // RED
  Serial.println("Color: RED");
  delay(1000); // Wait for 1 second

  // Set display to GREEN
  M5.dis.fillpix(0x00FF00); // GREEN
  Serial.println("Color: GREEN");
  delay(1000); // Wait for 1 second

  // Set display to BLUE
  M5.dis.fillpix(0x0000FF); // BLUE
  Serial.println("Color: BLUE");
  delay(1000); // Wait for 1 second

  // Set display to CYAN (Green + Blue)
  M5.dis.fillpix(0x00FFFF); // CYAN
  Serial.println("Color: CYAN");
  delay(1000); // Wait for 1 second

  // Set display to MAGENTA (Red + Blue)
  M5.dis.fillpix(0xFF00FF); // MAGENTA
  Serial.println("Color: MAGENTA");
  delay(1000); // Wait for 1 second

  // Set display to YELLOW (Red + Green)
  M5.dis.fillpix(0xFFFF00); // YELLOW
  Serial.println("Color: YELLOW");
  delay(1000); // Wait for 1 second

  // Set display to WHITE (Red + Green + Blue)
  M5.dis.fillpix(0xFFFFFF); // WHITE
  Serial.println("Color: WHITE");
  delay(1000); // Wait for 1 second
}

void setup()
{
  // Initialize M5Atom and Serial communication
  M5.begin(true, false, true);
  M5.dis.fillpix(0xFFFFFF); // WHITE
  Serial.println("Begin.");
}

void loop()
{
  // Call the cycleColors function to change colors
  /*
    cycleColors();

    if (M5.Btn.wasPressed())
    {
      Serial.println("Button was pressed!");
      M5.dis.fillpix(0x0000FF); // BLUE
      delay(1000);
    }

    if (M5.Btn.isReleased())
    {
      Serial.println("Button is released!");
    }

    if (M5.Btn.isPressed())
    {
      Serial.println("Button is pressed");
      M5.dis.fillpix(0xFF0000); // RED
      Serial.println("Color: RED");
    }

    if (M5.Btn.pressedFor(3000))
    {
      M5.dis.fillpix(0xFFFFFF); // WHITE
      Serial.println("Color: WHITE");
      delay(1000); // Wait for 1 second;
    }
  */

  if (M5.Btn.pressedFor(2000))
  {
    M5.dis.fillpix(0x0000FF); // BLUE
    Serial.println("Color: BLUE");
  }

  if (M5.Btn.isReleased())
  {
    Serial.println("Button is released!");
    M5.dis.fillpix(0xFFFFFF); // WHITE
    Serial.println("Color: WHITE");
  }

  delay(50);
  M5.update();
}

/*
        Button:
        M5.Btn.read();
        M5.Btn.isPressed();
        M5.Btn.isReleased();
        M5.Btn.wasPressed();
        M5.Btn.wasReleased();
        M5.Btn.wasreleasedFor()
        M5.Btn.pressedFor(uint32_t ms);
        M5.Btn.releasedFor(uint32_t ms);
        M5.Btn.lastChange();
*/