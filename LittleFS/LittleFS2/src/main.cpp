#include "ConfigSecure.h"
#include "NonBlockingTimer.h"
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

NonBlockingTimer myTimer(3000);

WebServer server(80);

void handleRoot()
{
  String savedContent = "";
  if (LittleFS.exists("/settings.txt")) {
    File file = LittleFS.open("/settings.txt", "r");
    if (file) {
      savedContent = file.readString();
      file.close();
    }
  }

  // Escape content for safe HTML embedding
  savedContent.replace("\"", "&quot;");
  savedContent.replace("<", "&lt;");
  savedContent.replace(">", "&gt;");

  // Use escaped content in HTML
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <style>
        body {
          background-color: #121212;
          color: #ffffff;
          font-family: Arial, sans-serif;
          display: flex;
          flex-direction: column;
          align-items: center;
          margin: 10px;
        }
        .container {
          width: 100%;
          max-width: 800px; /* Maximum width of the text area content */
          text-align: center;
        }
        textarea {
          max-width: 775px;
          width: 100%;
          height: 200px;
          margin-bottom: 10px;
          font-size: 16px;
          padding: 10px;
          background-color: rgb(209, 209, 209);
        }
        .buttons {
          display: flex;
          flex-direction: column;
          gap: 10px;
          width: 100%;
        }
        button {
          background-color: #6200ee;
          color: #ffffff;
          border: none;
          padding: 10px 20px;
          font-size: 16px;
          cursor: pointer;
          width: 100%;
        }
        button:hover {
          background-color: #3700b3;
        }
        .message {
          margin-top: 10px;
          font-size: 16px;
          color: #76ff03;
        }
      </style>
    </head>
    <body>
      <div class="container">
        <h1>ESP32 Web Interface</h1>
        <form action="/submit" method="POST">
          <textarea name="content">)rawliteral";
          html += savedContent;
          html += R"rawliteral(</textarea><br>
          <div class="buttons">
            <button type="submit">Submit</button>
            <button type="button" onclick="location.href='/settings'">Settings</button>
          </div>
        </form>
        <div class="message" id="status"></div>
        </div>
        <script>
          const params = new URLSearchParams(window.location.search);
          if (params.has('message')) {
            document.getElementById('status').innerText = params.get('message');
          }
        </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleSubmit()
{
  if (server.hasArg("content")) {
    String content = server.arg("content"); // Get raw content

    File file = LittleFS.open("/settings.txt", "w");
    if (!file) {
      server.send(500, "text/plain", "Failed to save content");
      return;
    }

    file.print(content); // Save raw content
    file.close();

    server.sendHeader("Location", "/?message=Content%20saved%20successfully", true);
    server.send(303);
  } else {
    server.sendHeader("Location", "/?message=No%20content%20provided", true);
    server.send(303);
  }
}

void handleSettings()
{
  if (LittleFS.exists("/settings.txt"))
  {
    File file = LittleFS.open("/settings.txt", "r");
    if (!file)
    {
      server.send(500, "text/plain", "Failed to read settings");
      return;
    }

    String content = file.readString();
    file.close();

    server.send(200, "text/plain", content);
  }
  else
  {
    server.send(404, "text/plain", "No settings found");
  }
}

void handleSetSettings()
{
  if (server.hasArg("plain")) { // Check if raw JSON payload exists
    String jsonData = server.arg("plain");
    Serial.println("Received JSON:");
    Serial.println(jsonData);

    // Parse JSON
    //StaticJsonDocument<512> doc;
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
      Serial.print("JSON Parse Error: ");
      Serial.println(error.c_str());
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }

    // Example: Access JSON fields
    if (doc.containsKey("setting1")) {
      String setting1 = doc["setting1"];
      Serial.println("Setting1: " + setting1);
    }

    if (doc.containsKey("setting2")) {
      String setting2 = doc["setting2"];
      Serial.println("Setting2: " + setting2);
    }

    // Save the JSON data to a file
    File file = LittleFS.open("/settings.txt", "w");
    if (!file) {
      server.send(500, "application/json", "{\"error\":\"Failed to save JSON\"}");
      return;
    }
    file.print(jsonData);
    file.close();

    server.send(200, "application/json", "{\"message\":\"Settings saved successfully\"}");
  } else {
    server.send(400, "application/json", "{\"error\":\"No JSON payload found\"}");
  }
}

void setup()
{
  Serial.begin(115200);

  // Initialize LittleFS
  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount LittleFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  // Define server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.on("/settings", HTTP_GET, handleSettings);
  server.on("/set-settings", HTTP_POST, handleSetSettings); // New endpoint for JSON

  // Start the server
  server.begin();
}

void loop()
{
  server.handleClient();

  if (myTimer.isReady())
  {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
}
