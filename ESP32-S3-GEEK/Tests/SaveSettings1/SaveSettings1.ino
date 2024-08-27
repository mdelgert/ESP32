#include <Preferences.h>

Preferences preferences;

String ssid = "yourSSID";
String password = "yourPassword";

void setup() {
  Serial.begin(115200);

  // Initialize NVS
  if (!preferences.begin("storage", false)) {
    Serial.println("Failed to initialize NVS");
    return;
  }

  // Check if values are stored, if not save them
  if (preferences.isKey("ssid")) {
    ssid = preferences.getString("ssid");
    password = preferences.getString("password");

    Serial.println("Loaded values from NVS:");
    Serial.println(ssid);
    Serial.println(password);
  } else {
    Serial.println("No stored values, saving default values...");
    
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    
    Serial.println("Values saved to NVS.");
  }

  // Close preferences
  preferences.end();
}

void loop() {
  // Print the values to Serial every second
  Serial.println("Current SSID and Password:");
  Serial.println("SSID: " + ssid);
  Serial.println("Password: " + password);
  delay(1000); // Wait for 1 second
}
