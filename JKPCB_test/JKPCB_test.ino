// motorControl tab
void motorControl_setup();
void motorControl_main();
// intHandler tab
void intHandler_setup();
void intHandler_main();
// touchPanel
void touchPanel_setup();
void touchPanel_main();
// data over sound Receive Panel
void dosRecv_setup();
void dosRecv_main();
// using i2s with internal ADC (mic input)
void i2s_analog_setup();
void i2s_analog_main();
// buzzerControl
void buzzerControl_setup();


#include "chirp_sdk.h"

void setup() {
  Serial.begin(115200);
  //Serial.println("System started");

  intHandler_setup();
  //i2s_analog_setup();
  motorControl_setup();
  touchPanel_setup();
  //dosRecv_setup();
  buzzerControl_setup();
}

void loop() {
  //intHandler_main();
  //i2s_analog_main();
  //motorControl_main();
  touchPanel_main();
  //dosRecv_main();
}
