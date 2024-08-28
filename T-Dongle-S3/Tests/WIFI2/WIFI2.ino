#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "webpage.h"  // Include the webpage content

Preferences preferences;

const char *ssid = "ESP32_AP";
const char *password = "12345678";

WebServer server(80);

const char *wapKey = "wap";
const char *passwordKey = "password";

void handleRoot() {
  // Load saved WAP and PASSWORD
  preferences.begin("wifi-creds", false);
  String savedWAP = preferences.getString(wapKey, "");
  String savedPassword = preferences.getString(passwordKey, "");
  preferences.end();

  // Create a copy of the HTML template
  String pageContent = htmlPage;

  // Replace placeholders with actual values
  pageContent.replace("%WAP%", savedWAP);
  pageContent.replace("%PASSWORD%", savedPassword);

  // Send the HTML page to the client
  server.send(200, "text/html", pageContent);
}

void handleSubmit() {
  String wap = server.arg("wap");
  String pass = server.arg("password");

  Serial.print("WAP: ");
  Serial.println(wap);
  Serial.print("PASSWORD: ");
  Serial.println(pass);

  // Save WAP and PASSWORD to Preferences
  preferences.begin("wifi-creds", false);
  preferences.putString(wapKey, wap);
  preferences.putString(passwordKey, pass);
  preferences.end();

  server.send(200, "text/plain", "Received and saved WAP and PASSWORD");
}

void setup() {
  Serial.begin(115200);

  // Initialize Preferences
  preferences.begin("wifi-creds", false);

  // Load saved WAP and PASSWORD
  String savedWAP = preferences.getString(wapKey, "");
  String savedPassword = preferences.getString(passwordKey, "");

  preferences.end();

  if (savedWAP != "" && savedPassword != "") {
    Serial.println("Loaded WAP and PASSWORD from preferences:");
    Serial.print("WAP: ");
    Serial.println(savedWAP);
    Serial.print("PASSWORD: ");
    Serial.println(savedPassword);
  } else {
    Serial.println("No WAP and PASSWORD saved in preferences.");
  }
I 
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
