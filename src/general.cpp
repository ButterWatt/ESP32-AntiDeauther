#include <Arduino.h>
#include "melody.h"
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
