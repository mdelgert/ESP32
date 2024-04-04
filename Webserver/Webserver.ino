#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

// Function prototype
void handleIncomingMessage();

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

WebServer server(80);

const char* indexHTML = R"(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Message Sender</title>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<style>
  body {
    background-color: #222;
    color: #eee;
    font-family: Arial, sans-serif;
  }
  #message-form {
    margin: 20px;
  }
  label {
    display: block;
    margin-bottom: 5px;
  }
  input[type="text"] {
    padding: 8px;
    width: 100%;
    margin-bottom: 10px;
    border: 1px solid #333;
    background-color: #444;
    color: #eee;
  }
  button[type="submit"] {
    padding: 8px 16px;
    border: none;
    background-color: #3498db;
    color: #fff;
    cursor: pointer;
  }
  button[type="submit"]:hover {
    background-color: #2980b9;
  }
  #response {
    margin-top: 10px;
    color: #aaffaa;
  }
</style>
</head>
<body>
  <div id="message-form">
    <form id="message-form">
      <label for="message">Message:</label>
      <input type="text" id="message" name="message">
      <button type="submit" id="submit">Submit</button>
    </form>
    <div id="response"></div>
  </div>
  <script>
    // Handle form submission
    $('#message-form').submit(function(event) {
      event.preventDefault(); // Prevent default form submission

      // Get message from input field
      var message = $('#message').val();

      // Send POST request to /message endpoint
      $.ajax({
        url: '/message',
        type: 'POST',
        contentType: 'application/json',
        data: JSON.stringify({ "message": message }),
        success: function(response) {
          $('#response').text("Message sent successfully.");
          $('#message').val(''); // Clear the input field
        },
        error: function(xhr, status, error) {
          $('#response').text("Error: " + xhr.responseText);
        }
      });
    });
  </script>
</body>
</html>
)";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print server details
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Route to handle POST request to "/message"
  server.on("/message", HTTP_POST, handleIncomingMessage);

  // Route to serve the HTML page
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", indexHTML);
  });

  server.begin();
  Serial.println("HTTP server started");

  // Set up mDNS responder
  if (!MDNS.begin("esp32")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
}

void loop() {
  server.handleClient();
}

// Function definition
void handleIncomingMessage() {
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

  // Send response to client
  server.send(200, "text/plain", "Message received successfully");
}
