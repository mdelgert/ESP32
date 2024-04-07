#include "M5StickCPlus2.h"
#include "Unit_MiniEncoderC.h"

UNIT_MINIENCODERC sensor;
uint16_t delay_time = 0;
uint8_t i2c_address = 0;

void page_get_encoder(void) {

  int32_t encoder_value = sensor.getEncoderValue();

  // Limit no more than 100
  if (encoder_value >= 100) {
    sensor.setEncoderValue(100);
  }

  // Limit do not go below zero
  if (encoder_value <= 0) {
    sensor.setEncoderValue(0);
  }

  // Convert encoder_value to string
  char encoder_str[20];
  sprintf(encoder_str, "%ld", encoder_value);
  StickCP2.Display.clear();
  StickCP2.Display.drawString(encoder_str, StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
  //Serial.println(encoder_value);
  //delay(500);
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
  sensor.setLEDColor(1, 0x000011);
}

void loop() {
  StickCP2.update();
  if (StickCP2.BtnA.wasPressed()) {
    StickCP2.Speaker.tone(8000, 20);
    StickCP2.Display.clear();
    StickCP2.Display.drawString("A Btn Pressed", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
    sensor.resetCounter();
  }

  page_get_encoder();
}
