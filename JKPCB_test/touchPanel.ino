#include <Adafruit_MPR121.h>
#include <Wire.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#define INTERVAL      10000

#define TOUCH_IRQ_PIN   12
#define LED_PIN         19

void  motorControl_fwd();
void motorControl_brake();
void buzzer_test();
void playSampleSong();
void buzzer_hello_world();
void buzzer_wrongInput();
void set_door_is_opened();
boolean isDoorOpen();
void closeDoor();

uint16_t getIntPhoto1Obtain();
uint16_t getIntPhoto2Obtain();
void setIntPhoto1Obtain(uint16_t val);
void setIntPhoto2Obtain(uint16_t val);
void setIntTouchIRQObtain(uint16_t val);
void enablePhoto1Int();
void enablePhoto2Int();
void enablePIRInt();
void disablePhoto1Int();
void disablePhoto2Int();
void disablePIRInt();
void disableTouchInt();
void enableTouchInt();

void dosRecv_main();
boolean isValidSound();
void setValidSound(boolean b);
void buzzer_touchPanel(unsigned int key_index);

void now_sendMessage(String msg);

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();


// Keeps track of the last pins touched, so that we can know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

const int INPUT_LIMIT = 32;
const char MAP[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0 , '#'};

char KEY_VAL[33] = {1, '#'};

unsigned int input_index = 0;
unsigned char inputVal[33] = {};
unsigned long time_limit = 0;
boolean isWokenUp = false;
boolean isValidInput = false;
boolean needToBlink = false;
boolean input_is_wrong = false;


void background_LED_on() {
  digitalWrite(LED_PIN, HIGH);
}

void background_LED_off() {
  digitalWrite(LED_PIN, LOW);
}

void compareInputWithKey() {
  boolean checker = false;

  for (int i = 0; i < input_index; i += 1) {
    if (KEY_VAL[i] != inputVal[i]) {
      // error message for debugging
      Serial.print("i = ");
      Serial.print(i);
      Serial.print("  =>  KEY_VAL[i] = ");
      Serial.print(((int) KEY_VAL[i]));
      Serial.print(", inputVal[i] = ");
      Serial.println(((int) inputVal[i]));

      checker = true;
      break;
    }
  }

  // check if the input did not match with the pattern.
  if (checker) {
    Serial.println("Invalid input!!");
    needToBlink = true;
    input_is_wrong = true;
    resetInput(); // reinitialise the global variables
    return;
  }

  Serial.println("Valid input!!");

  // reinitialise the array and index value
  input_index = 0;
  inputVal[33];

  isValidInput = true;
  //TODO isWokenUp = false;
}

void resetInput() {
    Serial.println("Initialise the input!");

    // reinitialise the array and index value
    input_index = 0;
    inputVal[33];

    time_limit = 0; // change the value of time limit to 0

    //TODO reset -> blink?
}

void setUpTimeLimit() {
    time_limit = millis() + INTERVAL;
}

void buildInput(uint16_t touchedKey) {
    //unsigned char keyChar = (unsigned char) touchedKey;
    unsigned char keyChar = (unsigned char) MAP[touchedKey];

    inputVal[input_index] = keyChar;
    input_index += 1;

    // use switch statement to check if the input character is either sharp characeter or astroid character.
    switch (keyChar) {
        case '*' :
            resetInput(); //reset the input to handle the astroid key
            setUpTimeLimit();
            needToBlink = true;
            break;
        case '#' :
            compareInputWithKey(); //compare the input values with the key
            break;
        default:
            Serial.print("Input = ");
            Serial.println(keyChar);
            setUpTimeLimit();
    }
}

void touchPanel_setup() {
  Serial.println("MPR121 Capacitive Touch sensor setup");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    return;
  }

  Serial.println("MPR121 found!");

  // This part is located in intHandler
  // set up interrupt source from MPR121 Touch IRQ
  // register TouchIRQ_ISR() as interrupt handler
  pinMode(TOUCH_IRQ_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TOUCH_IRQ_PIN), TouchIRQ_ISR, FALLING);

  pinMode(LED_PIN, OUTPUT);

  cap.setThresholds(5, 4);
}

void jiipKeyWakeUp() {
  Serial.println("jiipKeyWakeup()");
    isWokenUp = true;
    background_LED_on();
    setUpTimeLimit();
    disablePIRInt(); // diable PIR interrupt handler
    dosRecv_main();
}

void jiipKeySleep() {
    isWokenUp = false;
    resetInput();
    Serial.println("jiipKeySleep()");
    //disableTouchInt();
    currtouched = cap.touched();  // Just for flush buffer
    setIntTouchIRQObtain(0);
    //enableTouchInt();
    enablePIRInt();
    background_LED_off();
}

void getOneKey(){
  // Get the currently touched pads
  currtouched = cap.touched();

  if (!isWokenUp) {
      lasttouched = currtouched;
      intTouchIRQObtain = 0;

      jiipKeyWakeUp();
      return;
  }

  //TODO
  boolean isTouched = false;
  uint8_t touchedVal = 0;

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
        if (input_index < INPUT_LIMIT) {
            buildInput(i);
            touchedVal = i;
            isTouched = true;
        } else {
            needToBlink = true;
            input_is_wrong = true;

            //TODO
            input_index = 0;
            inputVal[33];
        }
    }
  }

  // reset our state
  lasttouched = currtouched;
  intTouchIRQObtain = 0;

  if (isTouched) buzzer_touchPanel(touchedVal);
}

void door_open() {
    if (isDoorOpen()) return;

    enablePhoto1Int();
    Serial.println("Start moving the motor - fwd");
    motorControl_fwd();

    while (getIntPhoto1Obtain() == 0) delay(10);

    Serial.println("interrupt occurred => intPhoto1Obtain");
    delay(100);
    motorControl_brake();
    setIntPhoto1Obtain(0);
    disablePhoto1Int();
    resetInput();

    Serial.println("Motor stopped");
    buzzer_hello_world();
    isValidInput = false;
    setValidSound(false);

    set_door_is_opened();
}

void led_blink() {
    if (input_is_wrong) {
        buzzer_wrongInput();
        //buzzer_test();
        //playSampleSong();
        input_is_wrong = false;
    }

    background_LED_off();
    delay(100);
    background_LED_on();
    delay(100);
    background_LED_off();
    delay(100);
    background_LED_on();
    needToBlink = false;
}

void process_timeout() {
    Serial.println("Timeout");
    jiipKeySleep();
    // reset our state
    lasttouched = currtouched;
    intTouchIRQObtain = 0;
}

boolean checker1 = false;

void touchPanel_main() {
//    if (time_limit != 0 && millis() > time_limit) {
//        process_timeout();
//        return;
//    }
    if (needToBlink) {
        led_blink();
        return;
    }
    if (isValidInput || isValidSound()) {
        if (checker1) {
            closeDoor();
            isValidInput = false;
            setValidSound(false);
            checker1 = false;
            jiipKeySleep();
        } else {
            door_open();
            checker1 = true;
        }
        //door_open();
        return;
    }
    if (intTouchIRQObtain == 0) return;
    getOneKey();
}


void touchPanel_test() {
  if (intTouchIRQObtain == 0) return;

  Serial.println("Touch IRQ");
  // Get the currently touched pads
  currtouched = cap.touched();
  Serial.print("currTouched : ");
  Serial.println(currtouched);

  boolean isTouched = false;
  uint8_t touchedVal = 0;

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      touchedVal = i;
      isTouched = true;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }
  // reset our state
  lasttouched = currtouched;
  intTouchIRQObtain = 0;

  if (isTouched) buzzer_touchPanel(touchedVal);
}

void open_close_test() {
    door_open();
    delay(2000);
    closeDoor();
    delay(2000);
}
