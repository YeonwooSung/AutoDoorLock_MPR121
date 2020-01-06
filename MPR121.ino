#include <Adafruit_MPR121.h>
#include <Wire.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint16_t numberIntObtain = 0;

// Interrupt handler for pin 36
void IRAM_ATTR gpio36_ISR() {
    // Interrupt flag on
    numberIntObtain = 1;
    // Get the currently touched pads
    //currtouched = cap.touched();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("System started");

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  // set up interrupt source from MPR121 Touch IRQ
  // register gpio36_ISR() as interrupt handler of GPIO pin 36
  pinMode(36, INPUT);
  attachInterrupt(36, gpio36_ISR, FALLING);
}

void loop() {
/*
  if(digitalRead(36) == 0 ) {
    Serial.print("pin 36 low\n");
  } 
*/

  if (numberIntObtain == 0) return;
 
  //if (numberIntObtain == 0 ) {
    Serial.print("Number Interrupt Obtained : ");
    Serial.println(numberIntObtain);
    //currtouched = cap.touched();
  //  numberIntObtain = 0;
  //} else return;

  // Get the currently touched pads => move into gpio36_ISR
  currtouched = cap.touched();
  /*
   if(digitalRead(36) == 0 ) {
        //Serial.println("pin 36 low\n");
        Serial.println("0");
        currtouched = cap.touched();
    } else Serial.println("1");
*/
  Serial.print("currTouched : ");
  Serial.println(currtouched);
  
  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched = currtouched;
  numberIntObtain = 0;
  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(100);
}
