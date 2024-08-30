#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <Preferences.h>
#include <ArduinoJson.h>
#include "Config.h"

struct DeviceSettings {
  String ssid;
  String password;
  String device_name;
  String admin_user;
  String admin_password;
  bool setup_mode;
  String mqtt_broker;
  int mqtt_port;
  String mqtt_topic;
  String mqtt_user;
  String mqtt_password;
  bool mqtt_certificate_enable;
  String mqtt_certificate;
};

class SettingsManager {
public:
  SettingsManager() : preferences() {}

  bool loadSettings(DeviceSettings& settings) {
    preferences.begin("settings", false);
    String storedJson = preferences.getString("json_data", "");
    preferences.end();

    if (storedJson.length() > 0) {
      DynamicJsonDocument doc(2048);  // Increase size to accommodate more fields
      DeserializationError error = deserializeJson(doc, storedJson);
      if (!error) {
        // Safely extract values with fallbacks to default values
        settings.setup_mode = doc.containsKey("device") && doc["device"].containsKey("setup_mode") ? doc["device"]["setup_mode"] : true;
        settings.ssid = doc.containsKey("wifi") && doc["wifi"].containsKey("ssid") ? doc["wifi"]["ssid"].as<String>() : DEFAULT_SSID;
        settings.password = doc.containsKey("wifi") && doc["wifi"].containsKey("password") ? doc["wifi"]["password"].as<String>() : DEFAULT_PASSWORD;
        settings.device_name = doc.containsKey("device") && doc["device"].containsKey("name") ? doc["device"]["name"].as<String>() : DEFAULT_DEVICE_NAME;
        settings.admin_user = doc.containsKey("device") && doc["device"].containsKey("admin") ? doc["device"]["admin"].as<String>() : DEFAULT_ADMIN;
        settings.admin_password = doc.containsKey("device") && doc["device"].containsKey("password") ? doc["device"]["password"].as<String>() : DEFAULT_ADMIN_PASSWORD;

        // Load MQTT settings
        settings.mqtt_broker = doc.containsKey("mqtt") && doc["mqtt"].containsKey("broker") ? doc["mqtt"]["broker"].as<String>() : "";
        settings.mqtt_port = doc.containsKey("mqtt") && doc["mqtt"].containsKey("port") ? doc["mqtt"]["port"].as<int>() : 1883;
        settings.mqtt_topic = doc.containsKey("mqtt") && doc["mqtt"].containsKey("topic") ? doc["mqtt"]["topic"].as<String>() : "";
        settings.mqtt_user = doc.containsKey("mqtt") && doc["mqtt"].containsKey("user") ? doc["mqtt"]["user"].as<String>() : "";
        settings.mqtt_password = doc.containsKey("mqtt") && doc["mqtt"].containsKey("password") ? doc["mqtt"]["password"].as<String>() : "";
        settings.mqtt_certificate_enable = doc.containsKey("mqtt") && doc["mqtt"].containsKey("certificate_enable") ? doc["mqtt"]["certificate_enable"] : false;
        settings.mqtt_certificate = doc.containsKey("mqtt") && doc["mqtt"].containsKey("certificate") ? doc["mqtt"]["certificate"].as<String>() : "";

        return true;
      }
    }
    // Use default settings if loading fails or JSON is not present
    setDefaultSettings(settings);
    return false;
  }

  void saveSettings(const String& json) {
    preferences.begin("settings", false);
    preferences.putString("json_data", json);
    preferences.end();
  }

private:
  Preferences preferences;

  void setDefaultSettings(DeviceSettings& settings) {
    settings.setup_mode = true;
    settings.ssid = DEFAULT_SSID;
    settings.password = DEFAULT_PASSWORD;
    settings.device_name = DEFAULT_DEVICE_NAME;
    settings.admin_user = DEFAULT_ADMIN;
    settings.admin_password = DEFAULT_ADMIN_PASSWORD;
    settings.mqtt_broker = "";
    settings.mqtt_port = 1883;
    settings.mqtt_topic = "";
    settings.mqtt_user = "";
    settings.mqtt_password = "";
    settings.mqtt_certificate_enable = false;
    settings.mqtt_certificate = "";
  }
};

#endif // SETTINGSMANAGER_H
