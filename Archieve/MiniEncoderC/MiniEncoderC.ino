#include "M5StickCPlus2.h"
#include "Unit_MiniEncoderC.h"

UNIT_MINIENCODERC sensor;
uint16_t delay_time = 0;
int32_t last_value = 0;
uint8_t i2c_address = 0;

void page_get_encoder(void) {
  int32_t encoder_value = sensor.getEncoderValue();
  Serial.print("Encoder Value: ");
  Serial.println(encoder_value);

  // Convert encoder_value to string
  // char encoder_str[20];
  // sprintf(encoder_str, "%ld", encoder_value);
  // StickCP2.Display.clear();
  // StickCP2.Display.drawString(encoder_str, StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
}

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  StickCP2.Display.setRotation(3);
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextDatum(middle_center);
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  StickCP2.Display.setTextSize(1);
  StickCP2.Display.drawString("Button Encoder", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
  sensor.begin(&Wire, MINIENCODERC_ADDR, 0, 26, 100000UL);
  delay_time = 20;
  i2c_address = sensor.getI2CAddress();
}

void get_inc_value(void) {
  int32_t inc_value = sensor.getIncrementValue();
  Serial.printf("Inc:%d", inc_value);

  // Convert encoder_value to string
  char encoder_str[20];
  sprintf(encoder_str, "%ld", inc_value);
  StickCP2.Display.clear();
  StickCP2.Display.drawString(encoder_str, StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
}

void loop() {

  bool btn_status = sensor.getButtonStatus();
  Serial.print("Button Status: ");
  Serial.println(btn_status);  // Print button status

  // Reset the sensor
  if (btn_status = true) {
    get_inc_value();
  } else {
    //sensor.resetCounter();
  }

  page_get_encoder();
  //delay(500);
}
