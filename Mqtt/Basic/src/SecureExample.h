// SecureExample.h
#pragma once

#include <Arduino.h>

// WiFi credentials
const char *ssid = "YourSSID";             // Replace with your WiFi name
const char *password = "YourPassword";    // Replace with your WiFi password

// MQTT Broker settings
const int mqtt_port = 1883;                // MQTT port (TLS)
const char *mqtt_broker = "yourserver.emqxsl.com"; // EMQX broker endpoint
const char *mqtt_topic = "testtopic/sub";     // MQTT topic
const char *mqtt_username = "emqx";        // MQTT username for authentication
const char *mqtt_password = "public";      // MQTT password for authentication