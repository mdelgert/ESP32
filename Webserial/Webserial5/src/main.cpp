#include <Arduino.h>
#include <WiFi.h>
#include <Esp.h>
#include "ImprovWiFiLibrary.h"

// Function declarations
void handleHttpRequest();

WiFiServer server(80);
ImprovWiFi improvSerial(&Serial);

char linebuf[80];
int charcount = 0;

void onImprovWiFiErrorCb(ImprovTypes::Error err)
{
    server.stop();
    // Trigger non-blocking blink
}

void onImprovWiFiConnectedCb(const char *ssid, const char *password)
{
    server.begin();
    // Trigger non-blocking blink
}

bool connectWifi(const char *ssid, const char *password)
{
    WiFi.begin(ssid, password);

    while (!improvSerial.isConnected())
    {
        // Trigger non-blocking blink
        // Ensure blinking updates while waiting
    }

    return true;
}

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    improvSerial.setDeviceInfo(ImprovTypes::ChipFamily::CF_ESP32_S3, "ImprovWiFiLib", "1.0.5", "BasicWebServer", "http://{LOCAL_IPV4}?name=Guest");
    improvSerial.onImprovError(onImprovWiFiErrorCb);
    improvSerial.onImprovConnected(onImprovWiFiConnectedCb);
    improvSerial.setCustomConnectWiFi(connectWifi); // Optional

    // Trigger non-blocking blink
}

void loop()
{
    improvSerial.handleSerial();

    if (improvSerial.isConnected())
    {
        handleHttpRequest();
    }

    // Update the non-blocking LED blink
}

void handleHttpRequest()
{
    WiFiClient client = server.available();
    if (client)
    {
        // Trigger non-blocking blink
        memset(linebuf, 0, sizeof(linebuf));
        charcount = 0;

        boolean currentLineIsBlank = true;
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                linebuf[charcount] = c;
                if (charcount < sizeof(linebuf) - 1)
                    charcount++;

                if (c == '\n' && currentLineIsBlank)
                {
                    // Send a standard HTTP response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close"); // Connection will close after response
                    client.println();
                    client.println("<!DOCTYPE HTML><html><head>");
                    client.println("<style>");
                    client.println("body { background-color: #121212; color:rgb(142, 142, 142); font-family: Arial, sans-serif; margin: 0; padding: 20px; }");
                    client.println("h1, h3 { color:rgb(142, 142, 142); }");
                    client.println("ul { list-style: none; padding: 0; }");
                    client.println("li { margin: 5px 0; }");
                    client.println("a { color:rgb(142, 142, 142); text-decoration: none; }");
                    client.println("a:hover { text-decoration: underline; }");
                    client.println("#welcome { font-size: 24px; margin-bottom: 20px; }");
                    client.println("</style>");
                    client.println("</head><body>");
                    client.println("<h1 id=\"welcome\">Welcome!</h1>");
                    client.println("<p>This is a simple webpage served by your ESP32</p>");
                    client.println("<h3>Chip Info</h3>");
                    client.println("<ul><li>Model:");
                    client.println(ESP.getChipModel());
                    client.println("</li><li>Cores: ");
                    client.println(ESP.getChipCores());
                    client.println("</li><li>Revision: ");
                    client.println(ESP.getChipRevision());
                    client.println("</li></ul>");
                    client.println("<h3>Network Info</h3>");
                    client.println("<ul><li>SSID: ");
                    client.println(WiFi.SSID());
                    client.println("</li><li>IP Address: ");
                    client.println(WiFi.localIP());
                    client.println("</li><li>MAC Address: ");
                    client.println(WiFi.macAddress());
                    client.println("</li></ul>");
                    client.println("<script>const params = new URLSearchParams(document.location.search);");
                    client.println("document.getElementById('welcome').innerHTML = 'Welcome' + (params.get(\"name\") ? ', ' + params.get('name') : '') + '!';");
                    client.println("</script>");
                    client.println("</body></html>");
                    break;
                }
            }
        }
        delay(1);
        client.stop();
    }
}
