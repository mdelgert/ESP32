#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

int counter = 1;  // Initialize a counter variable

void setup() {
  // Initialize the serial communication at a baud rate of 115200
  Serial.begin(115200);

  Config_Init();
  LCD_Init();
  LCD_SetBacklight(100);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, WHITE);
  Paint_SetRotate(90);
  LCD_Clear(BLACK);
  delay(1000);

  while (!Serial);
  Paint_DrawString_EN(20, 50, "BEGIN", &Font20, BLACK, WHITE);
}

void loop() {
  // Create a string to hold the message with the counter value
  char message[30];
  sprintf(message, "Hello, World! %d", counter);

  // Display the message on the LCD
  Paint_DrawString_EN(20, 50, message, &Font20, BLACK, WHITE);

  // Print the message to the serial monitor
  Serial.printf(message);

  // Increment the counter
  counter++;

  // Wait
  delay(5000);
  LCD_Clear(BLACK);
  
}
