#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <WiFi.h>
#include <WebServer.h>
#include "SettingsManager.h"

WebServer server(80);
SettingsManager settingsManager;

void handleGetSettings() {
  DeviceSettings settings;
  settingsManager.loadSettings(settings);
  
  DynamicJsonDocument doc(2048);
  doc["wifi"]["ssid"] = settings.ssid;
  doc["wifi"]["password"] = settings.password;
  doc["device"]["name"] = settings.device_name;
  doc["device"]["admin"] = settings.admin_user;
  doc["device"]["password"] = settings.admin_password;
  doc["device"]["setup_mode"] = settings.setup_mode;

  // Add MQTT settings to JSON response
  doc["mqtt"]["broker"] = settings.mqtt_broker;
  doc["mqtt"]["port"] = settings.mqtt_port;
  doc["mqtt"]["topic"] = settings.mqtt_topic;
  doc["mqtt"]["user"] = settings.mqtt_user;
  doc["mqtt"]["password"] = settings.mqtt_password;
  doc["mqtt"]["certificate_enable"] = settings.mqtt_certificate_enable;
  doc["mqtt"]["certificate"] = settings.mqtt_certificate;

  String jsonResponse;
  serializeJson(doc, jsonResponse);

  server.send(200, "application/json", jsonResponse);
  Serial.println("Settings retrieved and sent:");
  Serial.println(jsonResponse);
}

void handleSetSettings() {
  String json = server.arg("plain");
  settingsManager.saveSettings(json);
  server.send(200, "application/json", "{\"status\":\"received\"}");
  Serial.println("Settings saved:");
  Serial.println(json);
}

void handlePostMessage() {
  String json = server.arg("plain");
  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
    return;
  }

  const char* message = doc["message"] | "No message provided";
  Serial.printf("Message: %s\n", message);
  server.send(200, "application/json", "{\"status\":\"message received\"}");
}

void handleReboot() {
  server.send(200, "text/plain", "Rebooting...");
  Serial.println("Rebooting...");
  delay(100);
  ESP.restart();
}

void connectToWiFi(const DeviceSettings& settings) {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(settings.ssid.c_str(), settings.password.c_str());
  
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nConnected to WiFi, IP: %s\n", WiFi.localIP().toString().c_str());
  } else {
    Serial.println("\nFailed to connect. Rebooting...");
    ESP.restart();
  }
}

void handleClearSettings() {
  settingsManager.clearSettings();
  server.send(200, "application/json", "{\"status\":\"settings cleared\"}");
  Serial.println("All settings cleared from preferences.");
}

void handleWebServerClient() {
  server.handleClient();
}

void setupWebServer() {
  DeviceSettings settings;
  settingsManager.loadSettings(settings);

  // Check if setup mode is true
  if (settings.setup_mode) {
    Serial.println("Setup mode is true. Using default values from Config.h.");

    // Override settings with default values from Config.h
    settings.ssid = DEFAULT_SSID;
    settings.password = DEFAULT_PASSWORD;
    settings.device_name = DEFAULT_DEVICE_NAME;
    settings.admin_user = DEFAULT_ADMIN;
    settings.admin_password = DEFAULT_ADMIN_PASSWORD;

    // Explicitly set WiFi mode to AP mode
    WiFi.mode(WIFI_AP);

    Serial.println("Creating WiFi Access Point...");

    // Set up the Access Point with the default SSID and password
    if (WiFi.softAP(settings.ssid.c_str(), settings.password.c_str())) {
      Serial.printf("Access Point SSID: %s\n", settings.ssid.c_str());
      Serial.printf("Password: %s\n", settings.password.c_str());
      Serial.printf("Device Name: %s\n", settings.device_name.c_str());
      Serial.printf("Admin User: %s\n", settings.admin_user.c_str());
      Serial.printf("Admin Password: %s\n", settings.admin_password.c_str());

      // Set the static IP address for the AP from Config.h
      if (!WiFi.softAPConfig(DEFAULT_LOCAL_IP, DEFAULT_GATEWAY, DEFAULT_SUBNET)) {
        Serial.println("AP Config Failed");
      } else {
        Serial.println("AP Config Success");
        Serial.print("Access Point IP Address: ");
        Serial.println(WiFi.softAPIP());
      }
    } else {
      Serial.println("Failed to start Access Point.");
    }
  } else {
    Serial.println("Setup mode is false. Connecting to WiFi...");
    connectToWiFi(settings);
  }

  server.on("/settings/get", HTTP_GET, handleGetSettings);
  server.on("/settings/set", HTTP_POST, handleSetSettings);
  server.on("/settings/clear", HTTP_POST, handleClearSettings);  // New endpoint to clear settings
  server.on("/message", HTTP_POST, handlePostMessage);
  server.on("/reboot", HTTP_POST, handleReboot);

  server.begin();
}

#endif // WEBSERVERHANDLER_H
