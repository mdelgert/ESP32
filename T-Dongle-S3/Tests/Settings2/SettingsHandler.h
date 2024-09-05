#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

bool saveSettings(const String& jsonString);
String getSettings();
void clearSettings();

#endif // SETTINGSHANDLER_H
