#include "pitches.h"

#define BUZZER_PIN        18
#define BUZZER_FREQ       1E5 //600
#define BUZZER_RESOLUTION 12 //10
#define BUZZER_CHANNEL    0


int melody_note[] = { // 곰세마리
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, //도도도도도
  NOTE_E5, NOTE_G5, NOTE_G5, NOTE_E5, NOTE_C5, //미솔솔미도
  NOTE_G5, NOTE_G5, NOTE_E5, NOTE_G5, NOTE_G5, NOTE_E5, //솔솔미솔솔미
  NOTE_C5, NOTE_C5, NOTE_C5, //도도도
  NOTE_G5, NOTE_G5, NOTE_E5, NOTE_C5, //솔솔미도
  NOTE_G5, NOTE_G5, NOTE_G5, //솔솔솔
  NOTE_G5, NOTE_G5, NOTE_E5, NOTE_C5, //솔솔미도
  NOTE_G5, NOTE_G5, NOTE_G5, //솔솔솔
  NOTE_G5, NOTE_G5, NOTE_E5, NOTE_C5, //솔솔미도
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, //솔솔솔라솔
  NOTE_C6, NOTE_G5, NOTE_C6, NOTE_G5, //도솔도솔
  NOTE_E5, NOTE_D5, NOTE_C5 //미레도
};

uint8_t noteDurations[] = { // 음의 길이 설정
  2000, 4, 8, 8, 4, 4, // 처음 진입은 2000/2000 = 1
  4, 8, 8, 4, 4, //2
  8, 8, 4, 8, 8, 4, //3
  4, 4, 2, //4
  4, 4, 4, 4, //5
  4, 4, 2, //6
  4, 4, 4, 4, //7
  4, 4, 2, //8
  4, 4, 4, 4, //9
  8, 8, 8, 8, 2, //10
  4, 4, 4, 4, //11
  4, 4, 2 //12
};

uint8_t melody_note_mario [] = {
  NOTE_E3, NOTE_E3, 0, NOTE_E3, 
  0, NOTE_C3, NOTE_E3, 0, 
  NOTE_G3, 0, 0, 0, 
  NOTE_G2, 0, 0, 0, 
  NOTE_C3, 0, 0, NOTE_G2, 
  0, 0, NOTE_E2, 0, 
  0, NOTE_A2, 0, NOTE_B2, 
  0, NOTE_AS2, NOTE_A2, 0, 
  NOTE_G2, NOTE_E3, NOTE_G3, NOTE_A3, 
  0, NOTE_F3, NOTE_G3, 0, 
  NOTE_E3, 0, NOTE_C3, NOTE_D3, 
  NOTE_B2, 0, 0, NOTE_C3, 
  0, 0, NOTE_G2, 0, 
  0, NOTE_E2, 0, 0, 
  NOTE_A2, 0, NOTE_B2, 0, 
  NOTE_AS2, NOTE_A2, 0, NOTE_G2, 
  NOTE_E3, NOTE_G3, NOTE_A3, 0, 
  NOTE_F3, NOTE_G3, 0, NOTE_E3, 
  0, NOTE_C3, NOTE_D3, NOTE_B2, 0, 0
};

uint8_t noteDurations_mario [] = {
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  9, 9, 9, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 9, 
  9, 9, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12,
};

uint8_t melody_note_hello [] = {
    NOTE_G2, NOTE_C3, NOTE_E3, NOTE_G3, 0
};

uint8_t noteDurations_hello [] = {
    8, 8, 8, 8, 12
};

uint8_t melody_note_wrongInput [] = {
    NOTE_F3, NOTE_F3, 0, NOTE_F3, NOTE_F3, 0
};

uint8_t noteDurations_wrongInput [] = {
    9, 9, 12, 9, 9, 12
};


void buzzerControl_setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RESOLUTION);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
}

void buzzer_wrongInput() {
    int sizeofArr = sizeof(melody_note_wrongInput);
    unsigned long int beepTime = 0;
    int melody_num = 0;

    while (melody_num < sizeofArr) {
        if (millis() - beepTime >= 2000 / noteDurations_wrongInput[melody_num]) {
            beepTime = millis();

            ledcWrite(BUZZER_CHANNEL, 0);
            ledcWriteTone(BUZZER_CHANNEL, melody_note_wrongInput[melody_num]); // ledcWriteTone(uint8_t channel, note_t note);

            melody_num += 1;

            if (melody_num == sizeofArr) {
                ledcWrite(BUZZER_CHANNEL, 0); // noTone() - ledcWrite(uint8_t channel, uint32_t duty);
                //melody_num = 0;
                beepTime = 0;
                break;
            }
        }
    }
}

void buzzer_hello_world() {
    int sizeofArr = sizeof(melody_note_hello);
    unsigned long int beepTime = 0;
    int melody_num = 0;

    while (melody_num < sizeofArr) {
        if (millis() - beepTime >= 2000 / noteDurations_hello[melody_num]) {
            beepTime = millis();

            ledcWrite(BUZZER_CHANNEL, 0);
            ledcWriteTone(BUZZER_CHANNEL, melody_note_hello[melody_num]); // ledcWriteTone(uint8_t channel, note_t note);

            melody_num += 1;

            if (melody_num == sizeofArr) {
                ledcWrite(BUZZER_CHANNEL, 0); // noTone() - ledcWrite(uint8_t channel, uint32_t duty);
                //melody_num = 0;
                beepTime = 0;
                break;
            }
        }
    }
}

void buzzer_supermario() {
  int sizeofArr = sizeof(melody_note_mario);
  unsigned long int beepTime = 0;
  int melody_num = 0;

  while (melody_num <= sizeofArr) {
      if (millis() - beepTime >= 2000 / noteDurations_mario[melody_num]) {
          beepTime = millis();

          ledcWrite(BUZZER_CHANNEL, 0);
          ledcWriteTone(BUZZER_CHANNEL, melody_note_mario[melody_num]); // ledcWriteTone(uint8_t channel, note_t note);

          melody_num += 1;

          if (melody_num == sizeofArr) {
              ledcWrite(BUZZER_CHANNEL, 0); // noTone() - ledcWrite(uint8_t channel, uint32_t duty);
              beepTime = 0;
              break;
          }
      }
  }
}

void playSampleSong() {
  Serial.println("Play sample song");
  unsigned long int beepTime = 0;
  int melody_num = 0;

  while (melody_num <= 50) {
    if (millis() - beepTime >= 2000 / noteDurations[melody_num]) {
      beepTime = millis();

      ledcWrite(BUZZER_CHANNEL, 0);
      ledcWriteTone(BUZZER_CHANNEL, melody_note[melody_num]); // ledcWriteTone(uint8_t channel, note_t note);

      melody_num += 1;

      if (melody_num == 50) {
        ledcWrite(BUZZER_CHANNEL, 0); // noTone() - ledcWrite(uint8_t channel, uint32_t duty);
        beepTime = 0;
        break;
      }
    }
  }
}
