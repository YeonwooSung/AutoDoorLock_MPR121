#define SWITCH_PIN        0      // Pin number for on-board switch
#define PHOTO1_PIN      35
#define PHOTO2_PIN      27
#define PIR_PIN         39
#define BAT_PIN         36
#define MSENSOR_PIN     34
#define TOUCH_IRQ_PIN   12

uint16_t intSWObtain = 0;
uint16_t intPIRObtain = 0;
uint16_t intPhoto1Obtain = 0;
uint16_t intPhoto2Obtain = 0;
uint16_t intMsensorObtain = 0;
uint16_t intTouchIRQObtain = 0;

uint16_t getIntPIRObtain() {
    return intPIRObtain;
}

void setIntPIRObtain(uint16_t val) {
    intPIRObtain = val;
}

uint16_t getIntMsensorObtain() {
    return intMsensorObtain;
}

uint16_t getIntPhoto2Obtain() {
    return intPhoto2Obtain;
}

void setIntPhoto2Obtain(uint16_t val) {
    Serial.print("set Photo2 : ");
    Serial.println( val );
    intPhoto2Obtain = val;
}

uint16_t getIntPhoto1Obtain() {
    return intPhoto1Obtain;
}

void setIntPhoto1Obtain(uint16_t val) {
    Serial.print("set Photo1 : ");
    Serial.println( val );
    intPhoto1Obtain = val;
}

void setIntMsensorObtain(uint16_t val) {
    Serial.print("Msensor : ");
    Serial.println( val );
    intMsensorObtain = val;
}

// Interrupt handler for Dev board on-board switch
void IRAM_ATTR SWITCH_ISR() {
    // Interrupt flag on
    intSWObtain = 1;
}

// Interrupt handler for 
void IRAM_ATTR PIR_ISR() {
    // Interrupt flag on
    intPIRObtain = 1;
}

// Interrupt handler for 
void IRAM_ATTR Photo1_ISR() {
    // Interrupt flag on
    intPhoto1Obtain = 1;
}

// Interrupt handler for 
void IRAM_ATTR Photo2_ISR() {
    // Interrupt flag on
    intPhoto2Obtain = 1;
}

// Interrupt handler for 
void IRAM_ATTR TouchIRQ_ISR() {
    // Interrupt flag on
    intTouchIRQObtain = 1;
}


// Interrupt handler for 
void IRAM_ATTR Msensor_ISR() {
    // Interrupt flag on
    intMsensorObtain = 1;
}

void enablePhoto1Int() {
    Serial.println("enable p1");
    attachInterrupt(digitalPinToInterrupt(PHOTO1_PIN), Photo1_ISR, FALLING);
}

void disablePhoto1Int() {
    Serial.println("disable p1");
    detachInterrupt(digitalPinToInterrupt(PHOTO1_PIN));
}

void enablePhoto2Int() {
    Serial.println("enable p2");
    attachInterrupt(digitalPinToInterrupt(PHOTO2_PIN), Photo2_ISR, FALLING);
}

void disablePhoto2Int() {
    Serial.println("disable p2");
    detachInterrupt(digitalPinToInterrupt(PHOTO2_PIN));
}

void enableMsensorInt() {
    Serial.println("enable M");
    attachInterrupt(digitalPinToInterrupt(MSENSOR_PIN), Msensor_ISR, FALLING);
}

void disableMsensorInt() {
    Serial.println("disable M");
    detachInterrupt(digitalPinToInterrupt(MSENSOR_PIN));
}

void enablePIRInt() {
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), PIR_ISR, FALLING);
}

void disablePIRInt() {
    detachInterrupt(digitalPinToInterrupt(PIR_PIN));
}

void intHandler_setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), SWITCH_ISR, FALLING);
    pinMode(PHOTO1_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PHOTO1_PIN), Photo1_ISR, FALLING);
    pinMode(PHOTO2_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PHOTO2_PIN), Photo2_ISR, FALLING);
    pinMode(PIR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), PIR_ISR, RISING);
    pinMode(MSENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(MSENSOR_PIN), Msensor_ISR, FALLING);
    pinMode(BAT_PIN, INPUT);
    //pinMode(TOUCH_IRQ_PIN, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(TOUCH_IRQ_PIN), TouchIRQ_ISR, FALLING);
}

/*
 * 
 */
void intHandler_main() {
//  int val = 0;
//  val = analogRead(PIR_PIN);
//  Serial.println(val);

//  Serial.print("BAT ");
//  Serial.println(analogRead(BAT_PIN));
  
  if(intSWObtain) {
    Serial.println("Interrupt from on-board switch");
    intSWObtain = 0;
  }
  if(intPIRObtain) {
    Serial.println("Interrupt from PIR happen");
    intPIRObtain = 0;
  }
  if(intPhoto1Obtain) {
    Serial.println("Interrupt from PHOTO1 happen");
    intPhoto1Obtain = 0;
  }
  if(intPhoto2Obtain) {
    Serial.println("Interrupt from PHOTO2 happen");
    intPhoto2Obtain = 0;
  }
  if(intMsensorObtain) {
    Serial.println("Interrupt from Msensor happen");
    intMsensorObtain = 0;
  }
}
