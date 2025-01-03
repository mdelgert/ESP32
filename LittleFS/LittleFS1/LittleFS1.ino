#include <LittleFS.h>
#include <ArduinoJson.h>

#define JSON_FILE "/config.json"

void setup() {
  Serial.begin(115200);

  // Attempt to initialize LittleFS
  //if (!LittleFS.begin(true)) { // 'true' forces formatting
  if (!LittleFS.begin()) {
    Serial.println("Error: LittleFS mount failed. Formatting now...");
    return;
  }

  Serial.println("LittleFS mounted successfully.");

  // Debug: Check total and used space
  size_t totalBytes = LittleFS.totalBytes();
  size_t usedBytes = LittleFS.usedBytes();
  Serial.printf("Total Space: %u bytes, Used: %u bytes, Free: %u bytes\n",
                totalBytes, usedBytes, totalBytes - usedBytes);

  // Ensure file exists; create default JSON if missing
  if (!LittleFS.exists(JSON_FILE)) {
    Serial.println("File does not exist. Creating a default JSON file...");
    saveJsonToFile();
  }

  // Read and display JSON
  readJsonFromFile();
}

void loop() {
  // Empty loop
  //readJsonFromFile();
  //delay(1000);
}

// Save JSON Data to File
void saveJsonToFile() {
  StaticJsonDocument<256> jsonDoc;

  // Add data to JSON object
  jsonDoc["password1"] = "defaultPass123";
  jsonDoc["password2"] = "defaultPass456";
  jsonDoc["device"] = "ESP32-S3";
  jsonDoc["setup_mode"] = true;

  File file = LittleFS.open(JSON_FILE, "w");
  if (!file) {
    Serial.println("Error: Failed to open file for writing.");
    return;
  }

  if (serializeJson(jsonDoc, file) == 0) {
    Serial.println("Error: Failed to write JSON to file.");
  } else {
    Serial.println("Default JSON saved successfully.");
  }

  file.close();
}

// Read JSON Data from File
void readJsonFromFile() {
  // Open file for reading
  File file = LittleFS.open(JSON_FILE, "r");
  if (!file) {
    Serial.println("Error: Failed to open file for reading.");
    return;
  }

  // Parse JSON
  StaticJsonDocument<256> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, file);
  file.close();

  if (error) {
    Serial.print("Error: Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }

  // Display JSON data
  Serial.println("JSON loaded successfully:");
  serializeJsonPretty(jsonDoc, Serial);
}
