#define LED_PIN 2 //On Board LED
#define MOTOR_REV_PIN   25
#define MOTOR_FWD_PIN   26
#define SYSTEM_ON_PIN   37
#define BUZZER_PIN      18
#define LED_BLUE_PIN    5
#define LED_RED_PIN     17
#define LED_GREEN_PIN   16
// #define LED_TOUCH   19 Only On/Off. will not use PWM

#define ONBOARD_LED_CHANNEL 0
#define MOTOR_REV_CHANNEL 1
#define MOTOR_FWD_CHANNEL 2
#define BUZZER_CHANNEL 3
#define LED_RED_CHANNEL 4
#define LED_GREEN_CHANNEL 5
#define LED_BLUE_CHANNEL 6

#define LED_FREQ  5000
#define MOTOR_FREQ 5000
#define BUZZER_FREQ 600

#define LED_RESOLUTION  10
#define MOTOR_RESOLUTION 10
#define BUZZER_RESOLUTION 10

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
 
// setting PWM properties
//const int freq = 5000;
//const int ledChannel = 0;
//const int resolution = 10; //Resolution 8, 10, 12, 15

void buzzer_test();

void motorControl_setup()
{
  pinMode(LED_PIN,OUTPUT);
  pinMode(MOTOR_REV_PIN, OUTPUT);
  pinMode(MOTOR_FWD_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // On Board LED
  ledcSetup(ONBOARD_LED_CHANNEL, LED_FREQ, LED_RESOLUTION);
  ledcAttachPin(LED_PIN, ONBOARD_LED_CHANNEL);

  // Motor Rev
  ledcSetup(MOTOR_REV_CHANNEL, MOTOR_FREQ, MOTOR_RESOLUTION);
  ledcAttachPin(MOTOR_REV_PIN, MOTOR_REV_CHANNEL);

    // MOTOR FWD
  ledcSetup(MOTOR_FWD_CHANNEL, MOTOR_FREQ, MOTOR_RESOLUTION);
  ledcAttachPin(MOTOR_FWD_PIN, MOTOR_FWD_CHANNEL);
  
    // LED Red
  ledcSetup(LED_RED_CHANNEL, LED_FREQ, LED_RESOLUTION);
  ledcAttachPin(LED_RED_PIN, LED_RED_CHANNEL);

    // LED Green
  ledcSetup(LED_GREEN_CHANNEL, LED_FREQ, LED_RESOLUTION);
  ledcAttachPin(LED_GREEN_PIN, LED_GREEN_CHANNEL);

    // LED Blue
  ledcSetup(LED_BLUE_CHANNEL, LED_FREQ, LED_RESOLUTION);
  ledcAttachPin(LED_BLUE_PIN, LED_BLUE_CHANNEL);

  // Buzzer
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
}

void motorControl_main() {
  //led_onboard_led_test();
  //led_rgb_test();
  //led_rgb_test2();
  //motorControl_test();

  //buzzer_test();
}

void buzzer_test() {
    Serial.println("BUZZER test1");
    ledcWrite(BUZZER_CHANNEL, 300);
    delay(2000);

    ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ / 2, BUZZER_RESOLUTION);

    Serial.println("BUZZER test2");
    ledcWrite(BUZZER_CHANNEL, 300);
    delay(2000);

    ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ / 3, BUZZER_RESOLUTION);

    Serial.println("BUZZER test3");
    ledcWrite(BUZZER_CHANNEL, 300);
    delay(2000);

    ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ / 4, BUZZER_RESOLUTION);

    Serial.println("BUZZER test4");
    ledcWrite(BUZZER_CHANNEL, 300);
    delay(2000);

    ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
}

void  led_onboard_led_test() {
    //PWM Value varries from 0 to 1023  
  Serial.println("10 % PWM");
  ledcWrite(ONBOARD_LED_CHANNEL, 102);
  delay(2000);
 
  Serial.println("20 % PWM");
  ledcWrite(ONBOARD_LED_CHANNEL,205);
  delay(2000);
 
  Serial.println("40 % PWM");
  ledcWrite(ONBOARD_LED_CHANNEL,410);
  delay(2000);
 
  Serial.println("70 % PWM");
  ledcWrite(ONBOARD_LED_CHANNEL,714);
  delay(2000);
 
  Serial.println("100 % PWM");
  ledcWrite(ONBOARD_LED_CHANNEL,1024);
  delay(2000);

   Serial.println("0 % PWM");
  ledcWrite(ONBOARD_LED_CHANNEL,0);
  delay(2000);
  //Continuous Fading
  /*
  Serial.println("Fadding Started");
  while(1)
  {
    // set the brightness of pin 2:
    ledcWrite(ONBOARD_LED_CHANNEL, brightness);
  
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 1023) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }
  */  
}

void  led_rgb_test() {
  int demoCount = 0;
  Serial.println("RGB LED Test");
  while(demoCount < 5)
  {
    // set the brightness 
    ledcWrite(LED_RED_CHANNEL, brightness);
    //ledcWrite(LED_GREEN_CHANNEL, brightness);
    ledcWrite(LED_BLUE_CHANNEL, brightness);
  
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 1023) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }
}

void  led_rgb_test2() {
  int demoCount = 0;
  Serial.println("RGB LED Test");
  int colors[3] = {LED_RED_CHANNEL, LED_GREEN_CHANNEL, LED_BLUE_CHANNEL};

  for (int i = 0; i < 3; i++) {
    int col = colors[i];
    
    while(brightness < 1023)
    {
      // set the brightness 
      ledcWrite(col, brightness);
      //ledcWrite(LED_GREEN_CHANNEL, brightness);
      //ledcWrite(LED_BLUE_CHANNEL, brightness);
    
      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;
    
      // reverse the direction of the fading at the ends of the fade:
//      if (brightness <= 0 || brightness >= 1023) {
//        fadeAmount = -fadeAmount;
//      }
      // wait for 30 milliseconds to see the dimming effect
      delay(10);
    }

    brightness = 0;
    ledcWrite(col, brightness);
  }
}
void  motorControl_fwd() {
      ledcWrite(MOTOR_FWD_CHANNEL, 512);  // 50%
      ledcWrite(MOTOR_REV_CHANNEL, 0);
}

void  motorControl_rev() {
      ledcWrite(MOTOR_FWD_CHANNEL, 0);  
      ledcWrite(MOTOR_REV_CHANNEL, 512);  // 50%
}

void  motorControl_brake() {
      ledcWrite(MOTOR_FWD_CHANNEL, 1024);  // 100%
      ledcWrite(MOTOR_REV_CHANNEL, 1024);  // 100%
}

void motorControl_test() {
  int demoCount = 0;
  Serial.println("Motor Control Test");
  while(demoCount < 5)
  {
    motorControl_fwd();
    // wait for 30 milliseconds to see the dimming effect
    delay(1000);
    motorControl_brake();
    delay(100);
    motorControl_rev();
    // wait for 30 milliseconds to see the dimming effect
    delay(1000);
    motorControl_brake();
    // wait for 30 milliseconds to see the dimming effect
    delay(100);
  }  
}
