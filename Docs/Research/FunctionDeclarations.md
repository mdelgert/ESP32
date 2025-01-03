GitHub Copilot
Function declarations (also known as function prototypes) are used to inform the compiler about the existence of functions before they are actually defined. This is particularly useful in C++ when the function definitions are placed after the setup() and loop() functions.

In your code, the function declarations are:

These declarations are necessary if the function definitions are placed after they are called in the code. If you remove these declarations, you need to ensure that the function definitions appear before any calls to these functions.

Example with Function Declarations
Example without Function Declarations
If you want to remove the function declarations, you need to move the function definitions before they are used in setup() or loop():

Conclusion
You can remove the function declarations if you move the function definitions before they are called in the setup() or loop() functions. If you prefer to keep the current structure, it's best to leave the function declarations in place.

