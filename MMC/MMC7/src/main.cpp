#include "SDCardHandler.h"

void setup()
{
    Serial.begin(115200);
    SDCardHandler::init();

    SDCardHandler::writeToLogFile("SDCardHandler initialized.\n");
    String logData = SDCardHandler::readLogFile();
    Serial.println(logData);
}

void loop()
{
    // SDCardHandler::update();

    static int logCounter = 0; // Counter to keep track of log entries
    logCounter++;              // Increment the counter

    // Write an incremented log message to the log file
    SDCardHandler::writeToLogFile("Log Entry " + String(logCounter) + ": SDCardHandler is running.\n");

    // Read and print the entire log file contents
    String logData = SDCardHandler::readLogFile();
    Serial.println(logData);

    delay(1000);
}
