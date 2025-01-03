#include "BleKeyboard.h"
#include "KeyWeb.h"
#include "KeySettings.h"
#include "HtmlContent.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

BleKeyboard bleKeyboard("BleKeyServer", "Demo Inc.", 100);
DeviceSettings settings;
WebServer server(80);

void keyWebPrint(){
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(settings.SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void keyWebClient()
{
  server.handleClient();
}

void keyWebSetup() {
  settings = readSettings();
  // Connect to Wi-Fi
  WiFi.begin(settings.SSID, settings.Password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print server details
  keyWebPrint();

  // Route to handle POST request to "/message"
  server.on("/message", HTTP_POST, keyWebMessage);

  // Route to serve the HTML page
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", indexHTML); // Use the indexHTML constant from HtmlContent.h
  });

  server.begin();
  Serial.println("HTTP server started");

  // Set up mDNS responder
  if (!MDNS.begin(settings.Name)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  bleKeyboard.begin();
}

void keyWebMessage() {
  String message = server.arg("plain");

  // Print the received message before parsing
  Serial.print("Received message before parsing: ");
  Serial.println(message);

  StaticJsonDocument<200> doc;

  // Parse JSON
  DeserializationError error = deserializeJson(doc, message);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    server.send(400, "text/plain", "Invalid JSON format");
    return;
  }

  // Extract message from JSON
  const char* msg = doc["message"];

  // Print received message
  Serial.print("Received message: ");
  Serial.println(msg);
  
  //bleKeyboard.print(msg);
  bleKeyboard.println(msg);

  // Send response to client
  server.send(200, "text/plain", "Message received successfully");
}
