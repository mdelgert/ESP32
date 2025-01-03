/*
   Converted for ESP32-S3
   Source: github.com/spacehuhn/SimpleCLI
   Original: ESP8266 example

   Connect to the Access-Point, go to 192.168.4.1 and type "led on" or "led off".
 */

#define FASTLED_INTERNAL
#include <FastLED.h>  // FastLED library
#include <SimpleCLI.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Replace with your network credentials
#ifndef STASSID
#define STASSID "SimpleCLI"
#define STAPSK  "password"
#endif

// Wi-Fi and Server Setup
const char* ssid     = STASSID;
const char* password = STAPSK;

WebServer server(80);
SimpleCLI cli;

// LED Configuration
#define LED_DI_PIN 40
#define LED_CI_PIN 39

#define NUM_LEDS   1        // Number of LEDs in the strip
#define LED_TYPE   APA102  // Type of LED strip
#define COLOR_ORDER GRB     // LED color order

CRGB leds[NUM_LEDS];        // FastLED LED array

String  answer;
Command cmdLed;

void handleRoot() {
    // If data was sent
    if (server.args() > 0) {
        Serial.print("# ");
        Serial.println(server.arg("cmd"));

        cli.parse(server.arg("cmd"));

        if (cli.available()) {
            Command cmd = cli.getCommand();
            if (cmd == cmdLed) {
                String mode = cmd.getArgument("mode").getValue();

                if (mode == "on") {
                    leds[0] = CRGB::Green;  // Turn LED green
                    FastLED.show();
                    answer = "Turned LED ON";
                } else if (mode == "off") {
                    leds[0] = CRGB::Black;  // Turn LED off
                    FastLED.show();
                    answer = "Turned LED OFF";
                } else if (mode == "red") {
                    leds[0] = CRGB::Red;    // Turn LED red
                    FastLED.show();
                    answer = "Turned LED RED";
                } else if (mode == "blue") {
                    leds[0] = CRGB::Blue;   // Turn LED blue
                    FastLED.show();
                    answer = "Turned LED BLUE";
                } else {
                    answer = "Unknown mode. Use 'on', 'off', 'red', or 'blue'.";
                }
            }
        }

        if (cli.errored()) {
            answer = cli.getError().toString();
        }
    }

    // Build HTML response
    String html =
        "<!DOCTYPE html>"
        "<html>"
        "<head><title>LED Control</title></head>"
        "<body>"
        "<h1>LED Control</h1>"
        "<p>" + answer + "</p>"
        "<form action=\"index.html\" method=\"GET\">"
        "<input type=\"text\" name=\"cmd\" placeholder=\"led on/off/red/blue\"></input>"
        "<input type=\"submit\"></input>"
        "</form>"
        "</body>"
        "</html>";

    server.send(200, "text/html", html.c_str());
}

void handleNotFound() {
    server.send(404, "text/plain", "Not Found");
}

void setup() {
    Serial.begin(115200);

    // Initialize FastLED
    //FastLED.addLeds<LED_TYPE, LED_DI_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, LED_DI_PIN, LED_CI_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();

    // Configure Wi-Fi Access Point
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Start MDNS
    if (MDNS.begin("esp32s3")) {
        Serial.println("MDNS responder started");
    }

    // Setup server routes
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);

    // Register command
    cmdLed = cli.addCommand("led");
    cmdLed.addPositionalArgument("mode", "on");

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
    //MDNS.update();
}
