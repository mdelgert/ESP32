#include "Adafruit_TinyUSB.h"

// HID report descriptor using TinyUSB's template
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

// USB HID object
Adafruit_USBD_HID usb_hid;

// Keycodes for typing "hello"
const uint8_t keycodes_hello[] = {
  HID_KEY_H, HID_KEY_E, HID_KEY_L, HID_KEY_L, HID_KEY_O
};

void setup()
{
#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  TinyUSB_Device_Init(0); // Required for certain boards
#endif

  // Setup HID
  usb_hid.setBootProtocol(HID_ITF_PROTOCOL_KEYBOARD);
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.setStringDescriptor("TinyUSB Keyboard");

  usb_hid.begin();

  // Wait until USB is mounted
  while (!TinyUSBDevice.mounted()) {
    delay(10);
  }

  Serial.begin(115200);
  Serial.println("TinyUSB HID Keyboard Initialized");
}

void loop()
{
  // Wait 1 second between each typing
  delay(1000);

  // Wake up the host if suspended
  if (TinyUSBDevice.suspended()) {
    TinyUSBDevice.remoteWakeup();
  }

  // Ensure HID is ready
  if (!usb_hid.ready()) return;

  // Send each letter of "hello"
  for (uint8_t i = 0; i < sizeof(keycodes_hello); i++) {
    uint8_t keycode[6] = { keycodes_hello[i], 0, 0, 0, 0, 0 };

    usb_hid.keyboardReport(0, 0, keycode); // Send key press
    delay(100);                            // Key press duration

    usb_hid.keyboardRelease(0);            // Release the key
    delay(50);                             // Short delay between keys
  }

  // Send Enter key (optional)
  uint8_t enter_key[6] = { HID_KEY_ENTER, 0, 0, 0, 0, 0 };
  usb_hid.keyboardReport(0, 0, enter_key);
  delay(100); // Key press duration
  usb_hid.keyboardRelease(0);

  Serial.println("Typed: hello");
}
