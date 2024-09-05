#include <Preferences.h>
#include <ArduinoJson.h>
#include "SettingsHandler.h"

Preferences preferences;

bool saveSettings(const String& jsonString) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        return false;
    }

    const char* deviceName = doc["device"]["name"];
    bool setupMode = doc["device"]["setup_mode"];
    const char* admin = doc["device"]["admin"];
    const char* devicePassword = doc["device"]["password"];
    const char* wifiSSID = doc["wifi"]["ssid"];
    const char* wifiPassword = doc["wifi"]["password"];

    preferences.begin("device", false);
    preferences.putString("name", deviceName);
    preferences.putBool("setup_mode", setupMode);
    preferences.putString("admin", admin);
    preferences.putString("password", devicePassword);

    preferences.begin("wifi", false);
    preferences.putString("ssid", wifiSSID);
    preferences.putString("password", wifiPassword);
    preferences.end();

    return true;
}

String getSettings() {
    preferences.begin("device", true);
    String deviceName = preferences.getString("name", "");
    bool setupMode = preferences.getBool("setup_mode", false);
    String admin = preferences.getString("admin", "");
    String devicePassword = preferences.getString("password", "");
    
    preferences.begin("wifi", true);
    String wifiSSID = preferences.getString("ssid", "");
    String wifiPassword = preferences.getString("password", "");
    preferences.end();

    if (deviceName.isEmpty() && wifiSSID.isEmpty()) {
        return "";
    }

    StaticJsonDocument<512> doc;
    doc["device"]["name"] = deviceName;
    doc["device"]["setup_mode"] = setupMode;
    doc["device"]["admin"] = admin;
    doc["device"]["password"] = devicePassword;
    doc["wifi"]["ssid"] = wifiSSID;
    doc["wifi"]["password"] = wifiPassword;

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

void clearSettings() {
    preferences.begin("device", false);
    preferences.clear();  // Clear device settings
    preferences.begin("wifi", false);
    preferences.clear();  // Clear WiFi settings
    preferences.end();
}
