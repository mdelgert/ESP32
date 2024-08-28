#include <WiFi.h>
#include <WebServer.h>
#include "webpage.h"  // Include the webpage content

const char *ssid = "ESP32_AP";
const char *password = "12345678";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleSubmit() {
  String wap = server.arg("wap");
  String pass = server.arg("password");

  Serial.print("WAP: ");
  Serial.println(wap);
  Serial.print("PASSWORD: ");
  Serial.println(pass);

  server.send(200, "text/plain", "Received WAP and PASSWORD");
}

void setup() {
  Serial.begin(115200);

  // Set up Access Point with default IP (192.168.4.1)
  WiFi.softAP(ssid, password);

  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Configure web server routes
  server.on("/", handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
