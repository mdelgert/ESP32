#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

#include <USB.h>
#include <USBHIDKeyboard.h> // Include USBHIDKeyboard library

// Replace with your network credentials
const char *ssid = "IOT1";
const char *password = "CHANGEME";

// Replace with your MQTT Broker, username, password, and topic
const char *mqtt_server = "b1";             // Example broker
const char *mqtt_topic = "device1/action";              // Your MQTT topic
const char *mqtt_user = "emqx";                         // MQTT username
const char *mqtt_password = "CHANGEME"; // MQTT password

WiFiClient espClient;
PubSubClient client(espClient);

USBHIDKeyboard Keyboard; // Create a USBHIDKeyboard object

struct MessageStruct
{
    String message;
    int x;
    int y;
    uint16_t fgColor; // Foreground color (text)
    uint16_t bgColor; // Background color
};

uint16_t getColorFromString(String colorName)
{
    if (colorName == "WHITE")
        return WHITE;
    else if (colorName == "BLACK")
        return BLACK;
    else if (colorName == "RED")
        return RED;
    else if (colorName == "GREEN")
        return GREEN;
    else if (colorName == "BLUE")
        return BLUE;
    else if (colorName == "YELLOW")
        return YELLOW;
    // Add more colors as needed
    else
        return WHITE; // Default color
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    // Allocate a buffer to hold the payload
    char jsonBuffer[length + 1];
    memcpy(jsonBuffer, payload, length);
    jsonBuffer[length] = '\0'; // Null-terminate the string

    // Parse the JSON
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonBuffer);

    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    // Fill the struct with data
    MessageStruct msg;
    msg.message = doc["message"].as<String>();
    msg.x = doc["x"];
    msg.y = doc["y"];
    msg.fgColor = getColorFromString(doc["fgColor"].as<String>()); // Foreground color
    msg.bgColor = getColorFromString(doc["bgColor"].as<String>()); // Background color

    // Send the entire message as a series of keypresses
    Keyboard.begin();            // Start the keyboard
    Keyboard.print(msg.message); // Send the message as keypresses
    Keyboard.end();              // Stop the keyboard

    // Print the parsed data to the serial
    Serial.println("Parsed message:");
    Serial.println(msg.message);
    Serial.print("X: ");
    Serial.println(msg.x);
    Serial.print("Y: ");
    Serial.println(msg.y);
    Serial.print("Foreground Color: ");
    Serial.println(doc["fgColor"].as<String>());
    Serial.print("Background Color: ");
    Serial.println(doc["bgColor"].as<String>());

    // Display the message on the screen with the specified colors
    LCD_Clear(BLACK);
    Paint_DrawString_EN(msg.x, msg.y, msg.message.c_str(), &Font20, msg.bgColor, msg.fgColor);
}

void setup()
{
    // Setup LCD and Serial
    Config_Init();
    LCD_Init();
    LCD_SetBacklight(100);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, WHITE);
    Paint_SetRotate(90);
    LCD_Clear(BLACK);
    delay(1000);

    while (!Serial)
        ;
    Paint_DrawString_EN(20, 50, "BEGIN", &Font20, BLACK, WHITE);

    // Set the MQTT server, topic, and callback function
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    // Connect to Wi-Fi
    setup_wifi();

    // Initialize USB AFTER Wi-Fi is connected
    USB.begin(); // Initialize USB functionality
}

void loop()
{
    // Ensure the ESP32 is connected to the MQTT broker
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    LCD_Clear(BLACK);
    Paint_DrawString_EN(20, 50, "Connecting..", &Font20, BLACK, WHITE);
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Convert IPAddress to String, then to const char*
    String ipString = WiFi.localIP().toString();
    LCD_Clear(BLACK);
    Paint_DrawString_EN(20, 50, ipString.c_str(), &Font20, BLACK, WHITE);
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        LCD_Clear(BLACK);
        Paint_DrawString_EN(20, 50, "Attempting MQTT connection...", &Font20, BLACK, WHITE);
        // Attempt to connect with the MQTT username and password
        if (client.connect("ESP32Client", mqtt_user, mqtt_password))
        {
            Serial.println("connected");
            LCD_Clear(BLACK);
            Paint_DrawString_EN(20, 50, "MQTT connected", &Font20, BLACK, WHITE);
            // Subscribe to the specified topic
            client.subscribe(mqtt_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            LCD_Clear(BLACK);
            Paint_DrawString_EN(20, 50, "MQTT failed rc", &Font20, BLACK, WHITE);
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
