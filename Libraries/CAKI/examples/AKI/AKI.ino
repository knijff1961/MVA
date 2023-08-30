
#include "CAKI.h"

#define PIN_ROOD_LINKS_1  11
#define PIN_ROOD_RECHTS_1 10
#define PIN_WIT_1         6
#define PIN_BUTTON_1      5

#define WIT_KNIPPER_FREQ   750     // 3/4 sec
#define ROOD_KNIPPER_FREQ  500     // 2x een halve sec

CAKI cAki(PIN_ROOD_LINKS_1, PIN_ROOD_RECHTS_1, PIN_WIT_1, WIT_KNIPPER_FREQ, ROOD_KNIPPER_FREQ);

void setup() {
  pinMode(PIN_BUTTON_1, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  int val = digitalRead(PIN_BUTTON_1);

  cAki.go(currentMillis, val);
}
