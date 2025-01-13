// SecureExample.h
#pragma once

#include <Arduino.h>

// WiFi credentials
const char *ssid = "YourSSID";             // Replace with your WiFi name
const char *password = "YourPassword";    // Replace with your WiFi password

// MQTT Broker settings
const int mqtt_port = 8883;                // MQTT port (TLS)
const char *mqtt_broker = "yourserver.emqxsl.com"; // EMQX broker endpoint
const char *mqtt_topic = "testtopic/sub";     // MQTT topic
const char *mqtt_username = "YourUser";        // MQTT username for authentication
const char *mqtt_password = "YourPassword";      // MQTT password for authentication

// SSL certificate for MQTT broker
// Load DigiCert Global Root G2, used by EMQX Public Broker: broker.emqx.io
static const char ca_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDjjCCAnagAwIBAgIQAzrx5qcRqaC7KGSxHQn65TANBgkqhkiG9w0BAQsFADBh
...
-----END CERTIFICATE-----
)EOF";