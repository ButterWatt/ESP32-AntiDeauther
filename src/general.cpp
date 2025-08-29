#inlcude <Arduino.h>
#include "melody.h"
#define buzzerPin 26
int len = sizeof(melody) / sizeof(melody[0]);
void playTone(int freq, int duration) {
  if (freq == 0) {        // nghỉ (rest)
    delay(duration);
    return;
  }
  ledcSetup(0, freq, 10);   // channel 0, freq Hz, 10-bit
  ledcAttachPin(buzzerPin, 0);
  ledcWriteTone(0, freq);
  delay(duration);
  ledcWriteTone(0, 0);      // tắt
}

void playMelody(int* melody, int* duration, int len) {
  for (int i = 0; i < len; i++) {
    playTone(melody[i], duration[i]);
    delay(duration[i] * 0.3);   // nghỉ giữa các nốt
  }
  ledcDetachPin(buzzerPin);
}
