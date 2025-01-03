#ifndef PREFERENCES_HANDLER_H
#define PREFERENCES_HANDLER_H

#include <Preferences.h>

class PreferencesHandler {
private:
    Preferences preferences;
    const char* namespaceName = "settings";  // Namespace for preferences

    PreferencesHandler() {}  // Private constructor for singleton

public:
    static PreferencesHandler& getInstance() {
        static PreferencesHandler instance;
        return instance;
    }

    void init() {
        preferences.begin(namespaceName, false);  // Initialize Preferences with namespace
    }

    void setValue(const String& key, const String& value) {
        preferences.begin(namespaceName, false);
        preferences.putString(key.c_str(), value);
        preferences.end();
    }

    bool getValue(const String& key, String& outValue) {
        preferences.begin(namespaceName, true);
        outValue = preferences.getString(key.c_str(), "");
        preferences.end();
        return !outValue.isEmpty();
    }

    bool removeValue(const String& key) {
        preferences.begin(namespaceName, false);
        bool success = preferences.remove(key.c_str());
        preferences.end();
        return success;
    }

    void clear() {
        preferences.begin(namespaceName, false);
        preferences.clear();
        preferences.end();
    }
};

#endif // PREFERENCES_HANDLER_H
