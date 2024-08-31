#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

void initMqttClient();
void handleMqttClient();
void connectToMqtt();           // Declare the connectToMqtt function
void mqttCallback(char* topic, byte* payload, unsigned int length);  // Declare the mqttCallback function

#endif // MQTTHANDLER_H

