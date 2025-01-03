#include <Arduino.h>
#include <LittleFS.h> // Include the LittleFS library

void setup()
{
    Serial.begin(115200);

    //if (!LittleFS.begin()) // No formatting
    if (!LittleFS.begin(true)) // Format on fail
    {
        Serial.println("Failed to mount LittleFS");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    // Write to the file
    File writeFile = LittleFS.open("/example.txt", FILE_WRITE);
    if (writeFile)
    {
        writeFile.println("This is a test using LittleFS.");
        writeFile.close();
        Serial.println("File written successfully");
    }
    else
    {
        Serial.println("Failed to open file for writing");
        return;
    }
}

void loop()
{

    // Read the file
    File readFile = LittleFS.open("/example.txt", FILE_READ);
    if (readFile)
    {
        Serial.println("Reading file content:");
        while (readFile.available())
        {
            Serial.write(readFile.read());
        }
        readFile.close();
    }
    else
    {
        Serial.println("Failed to open file for reading");
    }

    delay(5000);
}
