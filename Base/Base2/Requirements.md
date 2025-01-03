Please provide template code of the following. Please just use header files to reduce the code.

### Summarized Coding Structure and Requirements

#### **Purpose**
To create a modular and maintainable Arduino ESP32 project structure for managing components (e.g., LEDs, buttons) and features (e.g., Bluetooth, Wi-Fi, WebSockets) with centralized configuration and logging.


#### **Structure**
1. **Centralized Configuration (`Config.h`)**
   - Stores feature flags, pin definitions, and default settings.
   - Example flags: `ENABLE_TFT`, `ENABLE_SERIAL`, `ENABLE_BLUETOOTH`.

2. **`LogManager`**
   - Handles all logging and message output to Serial, TFT, or other future destinations.
   - Provides methods like `init()` and `log(const String &message)` for initialization and message output.

3. **Modular Handlers**
   - **`LEDHandler`**: Controls FastLED light colors and states.
   - **`ButtonHandler`**: Manages OneButton single, double and long press and integrates with other components (e.g., toggling LEDs).
   - Handlers interact with `LogManager` for logging messages and maintaining clean separation of concerns.

4. **Feature-Specific Classes**
   - **`WiFiManager`**: Manages Wi-Fi connections, credentials, and preferences.
   - **`BluetoothHandler`**: Manages Bluetooth communication and callbacks.
   - **`WebSocketHandler`**: Manages WebSocket communication, message handling, and integration with other features.

5. **`main.ino`**
   - Delegates initialization and periodic updates to handlers and feature managers.
   - Ensures a clean and minimal `setup()` and `loop()`.

#### **Requirements**
1. **Encapsulation and Modularity**
   - Each feature or component should have its own class, encapsulating related logic and states.
   - Classes interact via dependency injection (e.g., `LogManager`).

2. **Centralized Logging**
   - Use `LogManager` for all message outputs (Serial, TFT, etc.).
   - Future extensibility for adding severity levels (`INFO`, `ERROR`, etc.) or logging to files.

3. **Centralized Configuration**
   - All pins, defaults, and feature flags in a single `Config.h` file.

4. **Non-blocking Logic**
   - Replace `delay()` with `millis()`-based timers where needed to maintain responsiveness.

5. **Debouncing for Buttons**
   - Use debouncing logic in `ButtonHandler` to avoid false triggers.

6. **Error Handling**
   - Robust checks for Wi-Fi, Bluetooth, and WebSocket connections with retries or fallbacks.

7. **Scalability**
   - Easily add or extend features (e.g., adding new handlers for sensors or actuators).

8. **Reusability**
   - The structure should be extensible to future projects with minimal changes.
