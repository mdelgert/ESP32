#include <Preferences.h>
#include <TFT_eSPI.h>  // Include the library for your TFT (e.g., Adafruit or TFT_eSPI)

// Preferences and TFT setup
Preferences preferences;
TFT_eSPI tft = TFT_eSPI();  // For TFT_eSPI library (configure User_Setup.h)

const char *namespaceName = "settings";  // Namespace for Preferences

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize TFT
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Display welcome message
  tft.println("Initializing...");

  // Initialize Preferences
  if (!preferences.begin(namespaceName, false)) {
    tft.println("Failed to open preferences!");
    while (true);  // Halt if preferences initialization fails
  }

  // Save a setting
  int savedValue = preferences.getInt("count", 0);  // Retrieve current count
  savedValue++;                                     // Increment the count
  preferences.putInt("count", savedValue);         // Save the updated count

  // Display the saved value on TFT
  tft.fillScreen(TFT_BLACK);  // Clear the screen
  tft.setCursor(10, 20);
  tft.println("Reboot Count:");
  tft.setCursor(10, 50);
  tft.println(savedValue);

  // Save a custom string
  preferences.putString("username", "ESP32_User");
  String username = preferences.getString("username", "default_user");

  // Display the username on TFT
  tft.setCursor(10, 100);
  tft.println("Username:");
  tft.setCursor(10, 130);
  tft.println(username);

  preferences.end();  // Close Preferences
}

void loop() {
  // Nothing to do here
}
    