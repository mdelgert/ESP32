#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// Define placeholders for the parameters
char mqttBroker[40] = "192.168.50.174";
char mqttPort[6] = "1883";
char mqttTopic[64] = "homeassistant/passtxt/";
char mqttUser[32] = "emqx";
char mqttPassword[32] = "public";

// WiFiManager instance
WiFiManager wm;

// Function to print Wi-Fi and MQTT settings
void printSettings()
{
    // Print Wi-Fi settings
    Serial.println("Wi-Fi Settings:");
    Serial.printf("SSID: %s\n", WiFi.SSID().c_str());
    Serial.printf("Password: %s\n", WiFi.psk().c_str());
    Serial.printf("Local IP: %s\n", WiFi.localIP().toString().c_str());

    // Print MQTT settings
    Serial.println("\nMQTT Settings:");
    Serial.printf("Broker: %s\n", mqttBroker);
    Serial.printf("Port: %s\n", mqttPort);
    Serial.printf("Topic: %s\n", mqttTopic);
    Serial.printf("Username: %s\n", mqttUser);
    Serial.printf("Password: %s\n", mqttPassword);
}

void setup()
{
    Serial.begin(115200);

    // Set WiFi mode to AP+STA (Access Point + Station)
    //WiFi.mode(WIFI_AP_STA);

    // Set a custom title for the portal
    wm.setTitle("Setup");

    // Customize button names in the menu
    //const char *menu[] = {"wifi", "param", "info", "u", "close", "restart", "exit"};
    //wm.setMenu(menu, 7);

    // Add custom CSS for buttons (change "Configure WiFi" text color)
    const char *customCSS = R"(
    <style>
        button, input[type='button'], input[type='submit'] {
            cursor: pointer;
            border: 0;
            background-color: #454242;
            color: #fffefe;
            line-height: 2.4rem;
            font-size: 1.2rem;
            width: 100%;
        }
        button.D {
            background-color: #690400;
        }
        header {
            text-align: center;
            margin-top: 20px;
            color: #ccc;
        }
    </style>
    <header>
        <p>My Custom Header - Powered by PassTxt</p>
    </header>
    )";

    // Style the WiFiManager portal
    wm.setCustomHeadElement(customCSS);
    wm.setClass("invert");

    // Wipe stored credentials for testing
    wm.resetSettings();

    // Add custom parameters
    WiFiManagerParameter customMqttBroker("mqtt_broker", "MQTT Broker", mqttBroker, 40);
    WiFiManagerParameter customMqttPort("mqtt_port", "MQTT Port", mqttPort, 6);
    WiFiManagerParameter customMqttTopic("mqtt_topic", "MQTT Topic", mqttTopic, 64);
    WiFiManagerParameter customMqttUser("mqtt_user", "MQTT Username", mqttUser, 32);
    WiFiManagerParameter customMqttPassword("mqtt_password", "MQTT Password", mqttPassword, 32);

    // Add parameters to WiFiManager
    wm.addParameter(&customMqttBroker);
    wm.addParameter(&customMqttPort);
    wm.addParameter(&customMqttTopic);
    wm.addParameter(&customMqttUser);
    wm.addParameter(&customMqttPassword);

    // Start the configuration portal
    //wm.setConfigPortalTimeout(0);

    // Start WiFiManager configuration portal
    if (!wm.autoConnect("PassTxtAP"))
    {
        Serial.println("Failed to connect.");
        ESP.restart();
    }
    else
    {
        Serial.println("Connected to WiFi!");
    }

    // Save custom parameters after successful configuration
    strcpy(mqttBroker, customMqttBroker.getValue());
    strcpy(mqttPort, customMqttPort.getValue());
    strcpy(mqttTopic, customMqttTopic.getValue());
    strcpy(mqttUser, customMqttUser.getValue());
    strcpy(mqttPassword, customMqttPassword.getValue());

    // Print saved settings
    Serial.println("\n--- Saved Settings ---");
    printSettings();
}

void loop()
{
    // Periodically print settings to confirm they are saved
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 5000)
    {
        lastPrint = millis();
        Serial.println("\n--- Current Settings ---");
        printSettings();
    }
}
