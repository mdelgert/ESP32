#define FASTLED_INTERNAL //remove annoying pragma messages -https://github.com/FastLED/FastLED/issues/1169
#include "Arduino.h"
#include "WebServerHandler.h" // Include the WebServerHandler header
#include "MqttHandler.h"      // Include the MqttHandler header
#include <WiFi.h>
#include "lv_driver.h"
#include <FastLED.h>
#include <OneButton.h>     // Include the OneButton library
#include <TFT_eSPI.h>  // Include the graphics library
#include "SecureConfig.h"     // Include the SecureConfig.h file

// Create an instance of the TFT_eSPI class
TFT_eSPI tft = TFT_eSPI();

//CRGB leds;

// Create an instance of the OneButton class
//OneButton button(BTN_PIN, true);

// Function declarations
// void handleClick();
// void handleDoubleClick();
// void handleLongPressStart();

void setup()
{
  Serial.begin(115200);  // Initialize Serial communication at 115200 baud rate
  delay(1000);           // Small delay to ensure the serial connection is ready

  tft.init();                // Initialize the display
  tft.setRotation(3);        // Set rotation to flip the screen
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color to white and background to black
  tft.setTextSize(2);        // Set text size to 2x the default size
  tft.setCursor(20, 30); // Position the cursor (may need adjusting based on rotation)
  tft.println("Start..."); // Print "Hello World" on the screen
  
  // FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(&leds, 1);
  // leds = CRGB::White;
  // FastLED.show();

  // Connect to Wi-Fi
  // Serial.print("Connecting to ");
  // Serial.println(DEFAULT_SSID);
  WiFi.begin(DEFAULT_SSID, DEFAULT_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    //leds = CRGB::Yellow;
    //FastLED.show();
    delay(1000);
    //tft.print(".");
    Serial.print(".");
  }

  // tft.fillScreen(TFT_BLACK);
  // tft.println("Wifi On");

  // Serial.println("");
  // Serial.println("WiFi connected.");
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());

  // leds = CRGB::Blue;
  // FastLED.show();

  // Initialize the web server
  initWebServer();

  // Initialize MQTT client
  initMqttClient();

  // Attach functions to button events
  // button.attachClick(handleClick);
  // button.attachDoubleClick(handleDoubleClick);
  // button.attachLongPressStart(handleLongPressStart);
}

void loop()
{
  // Handle web server requests
  handleWebServerClient();

  // Handle MQTT client tasks
  handleMqttClient();
}

// Function to handle a single click
void handleClick() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 30);
  tft.println("Clicked!"); // Display "Clicked!" message
}

// Function to handle a double-click
void handleDoubleClick() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 30);
  tft.println("Double Clicked!"); // Display "Double Clicked!" message
}

// Function to handle a long press
void handleLongPressStart() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 30);
  tft.println("Long Pressed!"); // Display "Long Pressed!" message
}