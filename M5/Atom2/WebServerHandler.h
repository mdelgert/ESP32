#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include "Config.h"  // Include the configuration file

// Create an instance of the web server on port 80
WebServer server(80);

// Preferences object to handle NVS (non-volatile storage)
Preferences preferences;

// Function to handle POST requests to save JSON settings data
void handlePostSettings() {
  String json = server.arg("plain");
  Serial.println("Received POST /settings request:");
  Serial.println(json);

  // Save the JSON data to preferences
  preferences.begin("settings", false);
  preferences.putString("json_data", json);
  preferences.end();

  server.send(200, "application/json", "{\"status\":\"received\"}");
  Serial.println("Settings saved and response sent.");
}

// Function to handle GET requests and return the saved JSON data
void handleGetSettings() {
  Serial.println("Received GET /settings request.");

  preferences.begin("settings", false);
  String storedJson = preferences.getString("json_data", "");
  preferences.end();

  if (storedJson.length() > 0) {
    server.send(200, "application/json", storedJson);
    Serial.println("Settings retrieved and sent:");
    Serial.println(storedJson);
  } else {
    server.send(404, "application/json", "{\"error\":\"No settings found\"}");
    Serial.println("No settings found.");
  }
}

// Function to handle POST requests to print a message to the serial monitor
void handlePostMessage() {
  String json = server.arg("plain");

  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.f_str());
    server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
    return;
  }

  const char* message = doc["message"] | "No message provided";
  Serial.println("Received POST /message request:");
  Serial.printf("Message: %s\n", message);

  server.send(200, "application/json", "{\"status\":\"message received\"}");
}

// Function to handle the reboot request via POST
void handleReboot() {
  Serial.println("Received POST /reboot request.");
  server.send(200, "text/plain", "Rebooting...");
  Serial.println("Rebooting response sent.");

  server.client().stop(); 
  delay(100); 
  ESP.restart(); 
}

// Function to set up the web server routes and check setup mode
void setupWebServer() {
  preferences.begin("settings", false);
  String storedJson = preferences.getString("json_data", "");
  preferences.end();

  const char* ssid;
  const char* password;
  const char* device_name;
  const char* admin_user;
  const char* admin_password;
  bool setup_mode = true; // Default to true if not specified

  if (storedJson.length() > 0) {
    Serial.println("Stored settings found:");
    Serial.println(storedJson);

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, storedJson);

    if (error) {
      Serial.print("Failed to parse JSON: ");
      Serial.println(error.f_str());
    } else {
      // Safely extract values with fallbacks to the default values in Config.h
      setup_mode = doc.containsKey("device") && doc["device"].containsKey("setup_mode") ? doc["device"]["setup_mode"] : true;
      ssid = doc.containsKey("wifi") && doc["wifi"].containsKey("ssid") ? doc["wifi"]["ssid"] : DEFAULT_SSID;
      password = doc.containsKey("wifi") && doc["wifi"].containsKey("password") ? doc["wifi"]["password"] : DEFAULT_PASSWORD;
      device_name = doc.containsKey("device") && doc["device"].containsKey("name") ? doc["device"]["name"] : DEFAULT_DEVICE_NAME;
      admin_user = doc.containsKey("device") && doc["device"].containsKey("admin") ? doc["device"]["admin"] : DEFAULT_ADMIN;
      admin_password = doc.containsKey("device") && doc["device"].containsKey("password") ? doc["device"]["password"] : DEFAULT_ADMIN_PASSWORD;
    }
  } else {
    Serial.println("No stored settings found. Using default values.");
    ssid = DEFAULT_SSID;
    password = DEFAULT_PASSWORD;
    device_name = DEFAULT_DEVICE_NAME;
    admin_user = DEFAULT_ADMIN;
    admin_password = DEFAULT_ADMIN_PASSWORD;
  }

  if (setup_mode) {
    Serial.println("Setup mode is true. Creating WiFi Access Point...");
    WiFi.softAP(ssid, password);
    Serial.printf("Access Point SSID: %s\n", ssid);
    Serial.printf("Password: %s\n", password);
    Serial.printf("Device Name: %s\n", device_name);
    Serial.printf("Admin User: %s\n", admin_user);
    Serial.printf("Admin Password: %s\n", admin_password);
    Serial.print("Access Point IP Address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Setup mode is false. Connecting to WiFi...");

    WiFi.begin(ssid, password);
    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {  // 10-second timeout
      delay(1000);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi");
      Serial.printf("SSID: %s\n", ssid);
      Serial.printf("Device Name: %s\n", device_name);
      Serial.printf("Admin User: %s\n", admin_user);
      Serial.printf("Admin Password: %s\n", admin_password);
      Serial.print("Local IP Address: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("\nFailed to connect to WiFi. Rebooting...");
      ESP.restart(); // Reboot if unable to connect
    }
  }

  server.on("/settings", HTTP_POST, handlePostSettings);
  server.on("/settings", HTTP_GET, handleGetSettings);
  server.on("/message", HTTP_POST, handlePostMessage);
  server.on("/reboot", HTTP_POST, handleReboot);
  server.begin();
}

void handleWebServerClient() {
  server.handleClient();
}

#endif // WEBSERVERHANDLER_H
