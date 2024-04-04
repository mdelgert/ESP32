//https://github.com/tkomde/M5StackBLEMouse/blob/master/M5StackBLEMouse.ino

#include "M5Atom.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDKeyboardTypes.h"
#include "sdkconfig.h"

enum ButtonState { NOT_PRESSED, PRESSED, PRINTED };

ButtonState currentState = NOT_PRESSED;

static BLEHIDDevice* hid;
BLECharacteristic* input2;
BLECharacteristic* output2;
BLECharacteristic* input1;
BLECharacteristic* output1;
bool isConnected = false;


class MyCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer){
    BLE2902* desc2;
    desc2 = (BLE2902*) input2->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
    desc2->setNotifications(true);
    BLE2902* desc1;
    desc1 = (BLE2902*) input1->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
    desc1->setNotifications(true);

    isConnected = true;
    Serial.println("Connecting process completed.");
  }

  void onDisconnect(BLEServer* pServer){
    isConnected = false;
  }
};

void StartBLEServer() {
  BLEServer *pServer;
  pServer = BLEDevice::createServer();
  Serial.println("Creating server...");

  //Instantiate hid device
  hid = new BLEHIDDevice(pServer);

  input2 = hid->inputReport(2); // <-- input REPORTID from report map
  output2 = hid->outputReport(2); // <-- output REPORTID from report map
  input1 = hid->inputReport(1); // <-- input REPORTID from report map
  output1 = hid->outputReport(1); // <-- output REPORTID from report map

  //set server callbacks
  pServer->setCallbacks(new MyCallbacks());

  /*
   * Set manufacturer name (OPTIONAL)
   * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.manufacturer_name_string.xml
   */
  std::string name = "esp-community"; //yes!
  hid->manufacturer()->setValue(name);

  /*
   * Set pnp parameters (MANDATORY)
   * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFilef2
   */
  hid->pnp(0x02, 0xe502, 0xa111, 0x0210);

  /*
   * Set hid informations (MANDATORY)
   * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.hid_information.xml
   */
  hid->hidInfo(0x00,0x01);

  /*
   * Mouse
   */
  const uint8_t reportMap[] = {

    // Mouse descriptor
    0x05, 0x01,                     // Usage Page (Generic Desktop)
    0x09, 0x02,                     // Usage (Mouse)
    0xA1, 0x01,                     // Collection (Application)
    
    // Report ID 1: Mouse motion
    0x85, 0x01,                     //      Report ID (MOUSE_XY_IN_REP_ID)
    0x09, 0x01,                     //      Usage (Pointer)
    0xA1, 0x00,                     //      Collection (Physical)
    0x75, 0x0C,                     //          Report Size (12)
    0x95, 0x02,                     //          Report Count (2)
    0x05, 0x01,                     //          Usage Page (Generic Desktop)
    0x09, 0x30,                     //          Usage (X)
    0x09, 0x31,                     //          Usage (Y)
    0x16, 0x01, 0xF8,               //          Logical maximum (2047)
    0x26, 0xFF, 0x07,               //          Logical minimum (-2047)
    0x81, 0x06,                     //          Input (Data, Variable, Relative)
    0xC0,                           //      End Collection (Physical)

    // Report ID 2: Mouse buttons + scroll/pan
    0x85, 0x02,                     //      Report ID (MOUSE_BTN_IN_REP_ID)
    0x09, 0x01,                     //      Usage (Pointer)
    0xA1, 0x00,                     //      Collection (Physical)
    0x95, 0x05,                     //          Report Count (5)
    0x75, 0x01,                     //          Report Size (1)
    0x05, 0x09,                     //          Usage Page (Buttons)
    0x19, 0x01,                     //          Usage Minimum (01)
    0x29, 0x05,                     //          Usage Maximum (05)
    0x15, 0x00,                     //          Logical Minimum (0)
    0x25, 0x01,                     //          Logical Maximum (1)
    0x81, 0x02,                     //          Input (Data, Variable, Absolute)
    0x95, 0x01,                     //          Report Count (1)
    0x75, 0x03,                     //          Report Size (3)
    0x81, 0x01,                     //          Input (Constant) for padding
    0x75, 0x08,                     //          Report Size (8)
    0x95, 0x01,                     //          Report Count (1)
    0x05, 0x01,                     //          Usage Page (Generic Desktop)
    0x09, 0x38,                     //          Usage (Wheel)
    0x15, 0x81,                     //          Logical Minimum (-127)
    0x25, 0x7F,                     //          Logical Maximum (127)
    0x81, 0x06,                     //          Input (Data, Variable, Relative)
    0xC0,                           //      End Collection (Physical)
    
    0xC0,                           // End Collection (Application)
  };
  
  /*
   * Set report map (here is initialized device driver on client side) (MANDATORY)
   * https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.report_map.xml
   */
  hid->reportMap((uint8_t*)reportMap, sizeof(reportMap));

  /*
   * We are prepared to start hid device services. Before this point we can change all values and/or set parameters we need.
   * We can setup characteristics authorization
   */
  hid->startServices();

  BLESecurity *pSecurity = new BLESecurity();
  pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);
  delay(1500);

  /*
   * setup advertising by providing appearance and advertised service.
   */
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setAppearance(HID_MOUSE);
  pAdvertising->addServiceUUID(hid->hidService()->getUUID());
  pAdvertising->start();
  Serial.println("Advertising started.");
}

void setup() {
  M5.begin();
  delay(50);
  M5.dis.drawpix(0, 0xff0000);
  Serial.println("Initializing...");

  // your setup code, to run once:
  BLEDevice::init("M5Stack-Mouse");
  StartBLEServer();
}

void MouseMove(short xRaw, short yRaw){
  //convert 12bit two's complement
  unsigned int xDiff = (xRaw ^ 0xfff + 1) & 0xfff;
  unsigned int yDiff = (yRaw ^ 0xfff + 1) & 0xfff;

  //set report value 
  uint8_t a[] = {0x0,0x0,0x0};        
  a[0] = (unsigned char)(xDiff & 0x0ff);
  a[1] = (unsigned char)((yDiff & 0x00f) * 16 + (xDiff >> 8));
  a[2] = (unsigned char)(yDiff >> 4);

  input1->setValue(a,sizeof(a));
  input1->notify();
}

void loop() {
    if (M5.Btn.isPressed()) {
        M5.dis.drawpix(0, 0x0000f0);
        if (currentState == NOT_PRESSED) {
            currentState = PRESSED;    
            Serial.println("Keypressed!");
            MouseMove(100,100);
        }
    } else {
        if (currentState == PRESSED) {
            currentState = PRINTED;
        } else if (currentState == PRINTED) {
            currentState = NOT_PRESSED;
            M5.dis.drawpix(0, 0xff0000);
        }
    }

    delay(50);
    M5.update();
}