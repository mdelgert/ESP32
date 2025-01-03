Yes, there are libraries and reusable patterns specifically designed to handle **non-blocking delays** in Arduino and similar environments, so you don’t need to keep writing custom logic. Here are some options and approaches you can adopt:

---

### **1. Use the `millis()` Pattern**

If you don’t want to use a library, you can encapsulate the `millis()` logic into a reusable class or function. Here’s an example:

#### **Reusable Non-Blocking Timer Class**
```cpp
#ifndef NON_BLOCKING_TIMER_H
#define NON_BLOCKING_TIMER_H

#include <Arduino.h>

class NonBlockingTimer {
private:
    unsigned long previousMillis;
    unsigned long interval;

public:
    NonBlockingTimer(unsigned long interval) : previousMillis(0), interval(interval) {}

    void setInterval(unsigned long newInterval) {
        interval = newInterval;
    }

    bool isReady() {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            return true;
        }
        return false;
    }

    void reset() {
        previousMillis = millis();
    }
};

#endif // NON_BLOCKING_TIMER_H
```

#### **Usage Example**
```cpp
#include "NonBlockingTimer.h"

NonBlockingTimer myTimer(1000); // 1-second timer

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (myTimer.isReady()) {
        Serial.println("Non-blocking delay triggered!");
    }
}
```

---

### **2. Use a Library**

Several libraries simplify non-blocking delay implementation:

#### **a. `SimpleTimer`**
- A lightweight library for managing timed tasks.
- Supports multiple timers and non-blocking execution.

**Installation**: Install via the Arduino Library Manager (`Sketch -> Include Library -> Manage Libraries`).

**Example Usage**:
```cpp
#include <SimpleTimer.h>

SimpleTimer timer;

void myTask() {
    Serial.println("Task executed!");
}

void setup() {
    Serial.begin(115200);

    // Set a timer to call myTask every 1000ms
    timer.setInterval(1000, myTask);
}

void loop() {
    timer.run(); // Run the timer
}
```

---

#### **b. `Ticker`**
- Designed for periodic execution of functions.
- Very lightweight and great for simple timers.

**Installation**: Install via the Arduino Library Manager.

**Example Usage**:
```cpp
#include <Ticker.h>

Ticker myTicker;

void myTask() {
    Serial.println("Ticker triggered!");
}

void setup() {
    Serial.begin(115200);

    // Call myTask every 1000ms
    myTicker.attach_ms(1000, myTask);
}

void loop() {
    // Nothing required here for Ticker
}
```

---

#### **c. `TaskScheduler`**
- A more advanced library for scheduling tasks.
- Supports task dependencies, priorities, and more.

**Installation**: Install via Arduino Library Manager.

**Example Usage**:
```cpp
#include <TaskScheduler.h>

Scheduler runner;

void myTaskCallback() {
    Serial.println("Task executed!");
}

Task myTask(1000, TASK_FOREVER, &myTaskCallback);

void setup() {
    Serial.begin(115200);

    runner.init();
    runner.addTask(myTask);
    myTask.enable();
}

void loop() {
    runner.execute();
}
```

---

### **3. Why Use a Library or Class?**

1. **Code Reusability**:
   - Encapsulate the delay logic into reusable functions or objects.

2. **Cleaner Code**:
   - Libraries like `Ticker` and `SimpleTimer` abstract away the `millis()` logic, making your code easier to read and maintain.

3. **Scalability**:
   - Manage multiple delays or scheduled tasks without duplicating logic.

---

### **Recommendation**

For simple, periodic tasks:
- Use the **`Ticker`** library if you only need a single task.

For multiple timers:
- Use **`SimpleTimer`** or **`TaskScheduler`**.

For lightweight custom logic:
- Use the **`NonBlockingTimer`** class above to encapsulate the `millis()` pattern.

This approach ensures you can reuse non-blocking delay logic without reimplementing it every time.