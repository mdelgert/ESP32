#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <USB.h>
#include <USBHIDMouse.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

// Replace with your network credentials
const char *ssid = "IOT1";
const char *password = "changeme";

// Replace with your MQTT Broker, username, password, and topic
const char *mqtt_server = "b1.local";                   // Example broker
const char *mqtt_topic = "device1/action";              // Your MQTT topic
const char *mqtt_user = "emqx";                         // MQTT username
const char *mqtt_password = "changme"; // MQTT password

// Define a unique client ID, e.g., based on the MAC address
String mqtt_client_id = "ESP32Client-" + String(WiFi.macAddress());

WiFiClient espClient;
PubSubClient client(espClient);

// Create a USBHIDMouse object
USBHIDMouse Mouse;

struct MessageStruct
{
    String action;
    int mouseX;
    int mouseY;
};

void callback(char *topic, byte *payload, unsigned int length)
{
    LCD_Clear(BLACK);
    Paint_DrawString_EN(20, 50, "Message arrived...", &Font20, BLACK, WHITE);

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
    msg.action = doc["action"].as<String>();
    msg.mouseX = doc["mouseX"].as<int>();
    msg.mouseY = doc["mouseY"].as<int>();

    // Display the action on the screen with the specified colors
    LCD_Clear(BLACK);
    Paint_DrawString_EN(20, 50, msg.action.c_str(), &Font20, BLACK, WHITE);

    // Print the parsed data to the serial
    Serial.println("Parsed action:");
    Serial.println(msg.action);

    // Handle the mouse action
    if (msg.action == "mouse")
    {
        LCD_Clear(BLACK);
        Paint_DrawString_EN(20, 50, "Mouse move...", &Font20, BLACK, WHITE);

        // Move the mouse
        Mouse.move(msg.mouseX, msg.mouseY);
        //Mouse.move(1000, 1000);
        Serial.println("Mouse moved");
    }
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

    // Connect to Wi-Fi
    setup_wifi();

    // Set the MQTT server, topic, and callback function
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    // Initialize USB and Mouse
    USB.begin();
    delay(1000); // Small delay to ensure the system is ready
    Mouse.begin();
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
    Paint_DrawString_EN(20, 50, "Connecting...", &Font20, BLACK, WHITE);
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

        // Attempt to connect with the MQTT username, password, and client ID
        if (client.connect(mqtt_client_id.c_str(), mqtt_user, mqtt_password))
        {
            Serial.println("connected");
            // Subscribe to the specified topic
            client.subscribe(mqtt_topic);
            LCD_Clear(BLACK);
            Paint_DrawString_EN(20, 50, "MQTT connected!", &Font20, BLACK, WHITE);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            LCD_Clear(BLACK);
            Paint_DrawString_EN(20, 50, "MQTT failed rc..", &Font20, BLACK, WHITE);
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
