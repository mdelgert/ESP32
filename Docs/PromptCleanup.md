### **AI Cleanup Prompt**
*"I have an Arduino C++ project for an ESP32 microcontroller. It includes features like Wi-Fi connection handling, WebSocket communication, and LED control. Please review my code and clean it up by:*

1. **Organizing the structure:** Refactor the code into reusable functions, classes, or modules for better readability and maintainability.
2. **Improving variable and function names:** Use descriptive, consistent naming conventions.
3. **Optimizing memory usage:** Use `PROGMEM` for constants where appropriate and reduce global variable usage.
4. **Enhancing readability:** Remove redundant code, add meaningful comments, and ensure consistent formatting (e.g., proper indentation and braces alignment).
5. **Adding error handling:** Include robust checks for operations like Wi-Fi connections, WebSocket setup, and SSL loading.
6. **Minimizing blocking calls:** Replace `delay()` with non-blocking logic using `millis()` for multitasking.
7. **Following Arduino best practices:** Keep the `loop()` function simple and delegate tasks to helper functions or classes.
8. **Separating configuration:** Move constants (like credentials, URLs, and retry delays) to a configuration file.
9. **Including debugging support:** Add optional debug logs controlled by preprocessor directives.

*Please return the cleaned-up code, following these guidelines and providing explanations for significant changes. If you notice specific issues, let me know how to address them."*