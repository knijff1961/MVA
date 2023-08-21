#include <CPreEmptiveTimer.h>

#define PIN_EERSTE_LED  11
#define PIN_TWEEDE_LED  10
#define PIN_DERDE_LED   6
#define PIN_VIERDE_LED  5

#define LED1_STATE_UP   1000    // 1 sec
#define LED1_STATE_DOWN 1000    // 1 sec
#define LED2_STATE_UP   700     // 700 ms
#define LED2_STATE_DOWN 700     // 700 ms
#define LED3_STATE_UP   650     // 650 ms
#define LED3_STATE_DOWN 650     // 650 ms
#define LED4_STATE_UP   1200    // 1200 ms
#define LED4_STATE_DOWN 1200    // 1200 ms


CPreEmptiveTimer cPreEmptiveTimer1;
CPreEmptiveTimer cPreEmptiveTimer2;
CPreEmptiveTimer cPreEmptiveTimer3;
CPreEmptiveTimer cPreEmptiveTimer4;

void setup() {
  pinMode(PIN_EERSTE_LED, OUTPUT);
  pinMode(PIN_TWEEDE_LED, OUTPUT);
  pinMode(PIN_DERDE_LED, OUTPUT);
  pinMode(PIN_VIERDE_LED, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if(cPreEmptiveTimer1.timeout(currentMillis)) {
    switch(cPreEmptiveTimer1.iState) {
      case 0:
        digitalWrite(PIN_EERSTE_LED, HIGH);               // LED aan
        cPreEmptiveTimer1.iState = 1;                     // nieuwe status
        cPreEmptiveTimer1.setWaitConst(LED1_STATE_UP);    // wacht ... sec
        break;
      case 1:
        digitalWrite(PIN_EERSTE_LED, LOW);                // LED uit
        cPreEmptiveTimer1.iState = 0;                     // nieuwe status
        cPreEmptiveTimer1.setWaitConst(LED1_STATE_DOWN);  // wacht ... sec
        break;
    }
  }

  if(cPreEmptiveTimer2.timeout(currentMillis)) {
    switch(cPreEmptiveTimer2.iState) {
      case 0:
        digitalWrite(PIN_TWEEDE_LED, HIGH);               // LED aan
        cPreEmptiveTimer2.iState = 1;                     // nieuwe status
        cPreEmptiveTimer2.setWaitConst(LED2_STATE_UP);    // wacht ... sec
        break;
      case 1:
        digitalWrite(PIN_TWEEDE_LED, LOW);                // LED uit
        cPreEmptiveTimer2.iState = 0;                     // nieuwe status
        cPreEmptiveTimer2.setWaitConst(LED2_STATE_DOWN);  // wacht ... sec
        break;
    }
  }

  if(cPreEmptiveTimer3.timeout(currentMillis)) {
    switch(cPreEmptiveTimer3.iState) {
      case 0:
        digitalWrite(PIN_DERDE_LED, HIGH);                // LED aan
        cPreEmptiveTimer3.iState = 1;                     // nieuwe status
        cPreEmptiveTimer3.setWaitConst(LED3_STATE_UP);    // wacht ... sec
        break;
      case 1:
        digitalWrite(PIN_DERDE_LED, LOW);                 // LED uit
        cPreEmptiveTimer3.iState = 0;                     // nieuwe status
        cPreEmptiveTimer3.setWaitConst(LED3_STATE_DOWN);  // wacht ... sec
        break;
    }
  }

  if(cPreEmptiveTimer4.timeout(currentMillis)) {
    switch(cPreEmptiveTimer4.iState) {
      case 0:
        digitalWrite(PIN_VIERDE_LED, HIGH);               // LED aan
        cPreEmptiveTimer4.iState = 1;                     // nieuwe status
        cPreEmptiveTimer4.setWaitConst(LED4_STATE_UP);    // wacht ... sec
        break;
      case 1:
        digitalWrite(PIN_VIERDE_LED, LOW);                // LED uit
        cPreEmptiveTimer4.iState = 0;                     // nieuwe status
        cPreEmptiveTimer4.setWaitConst(LED4_STATE_DOWN);  // wacht ... sec
        break;
    }
  }
}
