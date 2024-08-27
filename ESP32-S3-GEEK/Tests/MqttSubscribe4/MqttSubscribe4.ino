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
const char *password = "CHANGEME";

// Replace with your MQTT Broker, username, password, and topic
const char *mqtt_server = "b1.local";                   // Example broker
const char *mqtt_topic = "device1/action";              // Your MQTT topic
const char *mqtt_user = "emqx";                         // MQTT username
const char *mqtt_password = "CHANGEME"; // MQTT password

// Define a unique client ID, e.g., based on the MAC address
String mqtt_client_id = "ESP32Client-" + String(WiFi.macAddress());

WiFiClient espClient;
PubSubClient client(espClient);

// Create a USBHIDMouse object
USBHIDMouse Mouse;

// Timer-related variables
unsigned long timerInterval = 60000; // Default to 60 seconds
unsigned long lastTimer = 0;
bool jigEnabled = false; 

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

    // Handle the "jig" enable/disable command
    if (doc.containsKey("jig"))
    {
        jigEnabled = doc["jig"].as<bool>();
        LCD_Clear(BLACK);
        if (jigEnabled)
        {
            Paint_DrawString_EN(20, 50, "Jig Enabled", &Font20, BLACK, WHITE);
        }
        else
        {
            Paint_DrawString_EN(20, 50, "Jig Disabled", &Font20, BLACK, WHITE);
        }
        Serial.print("Jig set to: ");
        Serial.println(jigEnabled ? "Enabled" : "Disabled");
    }

    // Handle the timer interval setting
    if (doc.containsKey("timer"))
    {
        timerInterval = doc["timer"].as<unsigned long>() * 1000; // Convert seconds to milliseconds
        LCD_Clear(BLACK);
        Paint_DrawString_EN(20, 50, "Timer Set", &Font20, BLACK, WHITE);
        Serial.print("Timer set to: ");
        Serial.println(timerInterval);
    }

    // Optional: handle other actions
    // e.g., moving the mouse based on specific "action"
    if (doc.containsKey("action") && doc["action"] == "mouse")
    {
        int mouseX = doc["mouseX"].as<int>();
        int mouseY = doc["mouseY"].as<int>();
        LCD_Clear(BLACK);
        Paint_DrawString_EN(20, 50, "Mouse move...", &Font20, BLACK, WHITE);
        Mouse.move(mouseX, mouseY);
        Serial.println("Mouse moved by action command");
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

    while (!Serial);
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

    // Handle the timer for the jig
    if (jigEnabled && (millis() - lastTimer >= timerInterval))
    {
        // Move the mouse by 1 unit in both x and y directions
        Mouse.move(1, 1);
        Serial.println("Timer reached, mouse moved");

        // Reset the timer
        lastTimer = millis();
    }

    LCD_Clear(BLACK);
    if (jigEnabled)
    {
        Paint_DrawString_EN(20, 50, "Jig Enabled", &Font20, BLACK, WHITE);
    }
    else
    {
        Paint_DrawString_EN(20, 50, "Jig Disabled", &Font20, BLACK, WHITE);
    }
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
