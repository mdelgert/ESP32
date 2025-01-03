#ifndef HANDLER_TEMPLATE_H
#define HANDLER_TEMPLATE_H

#include "Config.h"
#include "LogManager.h"

class HandlerTemplate {
private:
    // Private members or states
    bool initialized;

    // Private helper method (optional)
    void privateHelper() {
        LogManager::log("HandlerTemplate private helper method called.");
    }

public:
    // Constructor
    HandlerTemplate() : initialized(false) {}

    // Initialization logic
    void init() {
        if (initialized) {
            LogManager::log("HandlerTemplate already initialized.");
            return;
        }

        // Perform initialization tasks
        LogManager::log("HandlerTemplate initialized.");
        initialized = true;
    }

    // Main update method (called periodically in the loop)
    void update() {
        if (!initialized) {
            LogManager::log("HandlerTemplate not initialized. Skipping update.");
            return;
        }

        // Add non-blocking logic for periodic tasks
        LogManager::log("HandlerTemplate update called.");
    }

    // Public action methods (examples)
    void performAction() {
        if (!initialized) {
            LogManager::log("HandlerTemplate not initialized. Action aborted.");
            return;
        }

        // Perform the desired action
        LogManager::log("HandlerTemplate performAction executed.");
    }

    // Error handling or cleanup
    void handleError(const String &errorMessage) {
        LogManager::log("HandlerTemplate error: " + errorMessage);
        // Add error-specific logic or recovery steps
    }

    void cleanup() {
        if (!initialized) {
            LogManager::log("HandlerTemplate not initialized. Cleanup skipped.");
            return;
        }

        // Perform cleanup tasks
        LogManager::log("HandlerTemplate cleanup completed.");
        initialized = false;
    }
};

#endif // HANDLER_TEMPLATE_H
