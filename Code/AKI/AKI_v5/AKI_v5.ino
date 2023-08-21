#include "CAKI.h"

#define PIN_ROOD_LINKS_1  11
#define PIN_ROOD_RECHTS_1 10
#define PIN_WIT_1         6
#define PIN_BUTTON_1      5

#define WIT_KNIPPER_FREQ_1   750     // 3/4 sec
#define ROOD_KNIPPER_FREQ_1  500     // 2x een halve sec

#define PIN_ROOD_LINKS_2  13
#define PIN_ROOD_RECHTS_2 12
#define PIN_WIT_2         9
#define PIN_BUTTON_2      8

#define WIT_KNIPPER_FREQ_2   650     // 650 ms
#define ROOD_KNIPPER_FREQ_2  512     // 512 ms

CAKI cAki_1(PIN_ROOD_LINKS_1, PIN_ROOD_RECHTS_1, PIN_WIT_1, WIT_KNIPPER_FREQ_1, ROOD_KNIPPER_FREQ_1);
CAKI cAki_2(PIN_ROOD_LINKS_2, PIN_ROOD_RECHTS_2, PIN_WIT_2, WIT_KNIPPER_FREQ_2, ROOD_KNIPPER_FREQ_2);

void setup() {
  pinMode(PIN_BUTTON_1, INPUT);
  pinMode(PIN_BUTTON_2, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  int val_1 = digitalRead(PIN_BUTTON_1);
  int val_2 = digitalRead(PIN_BUTTON_2);

  cAki_1.go(currentMillis, val_1);
  cAki_2.go(currentMillis, val_2);
}
