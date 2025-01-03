#include <RemoteDebug.h>
#include <LittleFS.h>

RemoteDebug Debug;

// File name for the log
const char *logFileName = "/debug.log";

// Custom output callback to log messages
void logToLittleFS(String message) {
    // Append message to the file
    File file = LittleFS.open(logFileName, FILE_APPEND);
    if (file) {
        file.println(message);
        file.close();
    } else {
        Serial.println("Failed to open log file for writing");
    }
}

void setup() {
    Serial.begin(115200);

    // Initialize LittleFS
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    // Initialize RemoteDebug
    Debug.begin("ESP32_Debug"); // Set the device name for RemoteDebug
    Debug.setCallbackOutput(logToLittleFS); // Set the custom logging callback
    Debug.setSerialEnabled(true);          // Enable Serial output as well

    Debug.println("Logging started"); // Example log
}

void loop() {
    // Process RemoteDebug
    Debug.handle();

    // Example log message
    Debug.println("This is a test log");
    delay(5000); // Log every 5 seconds
}
