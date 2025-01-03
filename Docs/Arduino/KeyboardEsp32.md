# Keyboard.press(KEY_LEFT_GUI); does not work on windows
https://github.com/espressif/arduino-esp32/issues/8380
https://github.com/hathach/tinyusb/blob/6c7c9f2ef5a80d5a6879e9c3558162188c6cf889/src/class/hid/hid.h#L522

void setup() {
  Keyboard.begin();
  USB.begin();
  delay(2000);

  Keyboard.pressRaw(HID_KEY_GUI_LEFT);
  Keyboard.pressRaw(HID_KEY_R);
  delay(500);
  Keyboard.releaseRaw(HID_KEY_GUI_LEFT);
  Keyboard.releaseRaw(HID_KEY_R);

  Keyboard.printf("notepad\n");
}