#define SWITCH_PIN        0      // Pin number for on-board switch
#define PHOTO1_PIN      35
#define PHOTO2_PIN      27
#define PIR_PIN         36
#define MSENSOR_PIN     34
#define TOUCH_IRQ_PIN   12

uint16_t intSWObtain = 0;
uint16_t intPIRObtain = 0;
uint16_t intPhoto1Obtain = 0;
uint16_t intPhoto2Obtain = 0;
uint16_t intMsensorObtain = 0;
uint16_t intTouchIRQObtain = 0;

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

void intHandler_setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), SWITCH_ISR, FALLING);
    pinMode(PHOTO1_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PHOTO1_PIN), Photo1_ISR, FALLING);
    pinMode(PHOTO2_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PHOTO2_PIN), Photo2_ISR, FALLING);
    pinMode(PIR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), PIR_ISR, FALLING);   
    pinMode(MSENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(MSENSOR_PIN), Msensor_ISR, FALLING);
    pinMode(TOUCH_IRQ_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(TOUCH_IRQ_PIN), TouchIRQ_ISR, FALLING);
}

/*
 * 
 */
void intHandler_main() {
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
  if(intTouchIRQObtain) {
    Serial.println("Interrupt from Touch happen");
    intTouchIRQObtain = 0;
  }  
}
