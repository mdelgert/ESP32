https://github.com/atanisoft/esp32usb

The USBHIDKeyboard library provides several key actions that can be used to simulate keyboard input. Here are some of the key actions and their typical use cases:

The USBHIDKeyboard library typically does not include print and println methods, as these are more commonly associated with serial communication libraries like Serial. However, if you are referring to sending strings of text via the keyboard, you can use the Keyboard.print and Keyboard.println methods provided by the Keyboard library in the Arduino environment.

Keyboard.print()
Description: Sends a string of characters as keyboard input.
Use Case: Use this to type out a string of text. Each character in the string is sent as a key press followed by a key release.

Keyboard.println()
Description: Sends a string of characters as keyboard input followed by a newline character.
Use Case: Use this to type out a string of text and then press the Enter key.

Keyboard.press(key):
Description: Simulates pressing a key down.
Use Case: Use this when you need to simulate holding down a key. For example, holding down the Shift key while pressing another key to type an uppercase letter.

Keyboard.release(key):
Description: Simulates releasing a key.
Use Case: Use this to release a key that was previously pressed. This is useful when you need to simulate key combinations where keys are pressed and released in sequence.

Keyboard.releaseAll():
Description: Releases all currently pressed keys.
Use Case: Use this to ensure that no keys are stuck in the pressed state. This is particularly useful after simulating key combinations to reset the keyboard state.

Keyboard.write(key):
Description: Simulates pressing and releasing a key.
Use Case: Use this for simple key presses where you do not need to hold the key down. For example, typing a single character or pressing the Enter key.

Keyboard.begin():
Description: Initializes the keyboard library.
Use Case: Call this in the setup() function to initialize the keyboard functionality before using any other keyboard functions.

Keyboard.end():
Description: Ends the keyboard functionality.
Use Case: Call this to stop the keyboard functionality when it is no longer needed.
Example Usage
Here is an example demonstrating the use of these functions:

#include <USBHIDKeyboard.h>

void setup() {
  Keyboard.begin();
}

void loop() {
  // Simulate pressing and holding the Ctrl key
  Keyboard.press(KEY_LEFT_CTRL);
  
  // Simulate pressing and releasing the 'C' key (e.g., for copy command)
  Keyboard.write('C');
  
  // Release the Ctrl key
  Keyboard.release(KEY_LEFT_CTRL);
  
  // Ensure all keys are released
  Keyboard.releaseAll();
  
  // Wait for a while before repeating
  delay(1000);

  // Type out "Hello, World!" followed by a newline
  Keyboard.println("Hello, World!");
  delay(1000);
}

Red: 0xff0000
Green: 0x00ff00
Blue: 0x0000ff
Yellow: 0xffff00
Cyan: 0x00ffff
Magenta: 0xff00ff
White: 0xffffff
Black: 0x000000
Orange: 0xffa500
Purple: 0x800080
Pink: 0xffc0cb
Brown: 0xa52a2a
Gray: 0x808080
Light Gray: 0xd3d3d3
Dark Gray: 0xa9a9a9