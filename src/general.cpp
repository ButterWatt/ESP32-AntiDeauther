#include <Arduino.h>
int melody[] = {
  659, 587, 370, 415, 554, 494, 294, 330,
  494, 440, 277, 330, 440
};

int duration[] = {
  130, 130, 130, 200, 130, 130, 130, 200,
  130, 130, 130, 200, 200
};

int len = sizeof(melody) / sizeof(melody[0]);
void playTone(int freq, int duration) {
  if (freq == 0) {        //rest
    delay(duration);
    return;
  }
  ledcSetup(0, freq, 10);   // channel 0, freq Hz, 10-bit
  ledcAttachPin(buzzerPin, 0);
  ledcWriteTone(0, freq);
  delay(duration);
  ledcWriteTone(0, 0);      // off
}
void playMelody(int* melody, int* duration, int len) {
  for (int i = 0; i < len; i++) {
    playTone(melody[i], duration[i]);
    delay(duration[i] * 0.3);   // rest every note
  }
  ledcDetachPin(buzzerPin);
}
