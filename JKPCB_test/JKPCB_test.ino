// motorControl tab
void motorControl_setup();
void motorControl_main();
void  motorControl_rev();
void motorControl_brake();
// intHandler tab
void intHandler_setup();
void intHandler_main();
void enablePhoto2Int();
void disablePhoto2Int();
void enableMsensorInt();
void disableMsensorInt();
uint16_t getIntMsensorObtain();
uint16_t getIntPhoto2Obtain();
void setIntPhoto2Obtain(uint16_t val);
void setIntMsensorObtain(uint16_t val);
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
void buzzer_supermario();


#include "chirp_sdk.h"

#define DOOR_OPEN_TIMEOUT 60000 //TODO


boolean door_is_opened = false;
boolean needToCheckTimer = false;
boolean needToCheckMSensor = false;
boolean needToCloseDoor = false;
unsigned long door_timer = 0;


boolean isDoorOpen() {
    return door_is_opened;
}

void setup_door_timer() {
    door_timer = millis() + DOOR_OPEN_TIMEOUT;
}

void init_door_timer() {
    door_timer = 0;
}

void set_door_is_opened() {
    needToCheckTimer = true;
    needToCheckMSensor = true;
    door_is_opened = true;
    setup_door_timer();

    enableMsensorInt();
}

void set_door_is_closed() {
    needToCheckTimer = false;
    needToCheckMSensor = false;
    door_is_opened = false;
    init_door_timer();

    disableMsensorInt();
}

void closeDoor() {
    enablePhoto2Int();
    Serial.println("Start moving the motor - rev");
    motorControl_rev();

    while (getIntPhoto2Obtain() == 0) delay(10);

    Serial.println("interrupt occurred => intPhoto2Obtain");
    motorControl_brake();
    setIntPhoto2Obtain(0);
    setIntMsensorObtain(0);
    disablePhoto2Int();

    set_door_is_closed();
}

void setup() {
    Serial.begin(115200);

    intHandler_setup();
    //i2s_analog_setup();
    motorControl_setup();
    touchPanel_setup();
    //dosRecv_setup();
    buzzerControl_setup();
}

void loop() {
    if (needToCloseDoor) {
        closeDoor();
        needToCloseDoor = false;
        return;
    }

    if (isDoorOpen()) {
        // check timeout  ->  alarm
        if (needToCheckTimer && millis() > door_timer) {
            buzzer_supermario();
        }

        //TODO check msensor_flag -> door close
        if (needToCheckMSensor && getIntMsensorObtain() != 0) {
            needToCloseDoor = true;
            return;
        }
    }

    //TODO if the door is closed, then the msensor interrupt should be disabled.

    //intHandler_main();
    //i2s_analog_main();
    //motorControl_main();
    touchPanel_main();
    //dosRecv_main();
}
