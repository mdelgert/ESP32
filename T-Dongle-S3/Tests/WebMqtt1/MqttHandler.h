#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

void initMqttClient();
void handleMqttClient();
void connectToMqtt();
void mqttCallback(char* topic, byte* payload, unsigned int length);
void sendHelloMessage();  // Declare the sendHelloMessage function

#endif // MQTTHANDLER_H
