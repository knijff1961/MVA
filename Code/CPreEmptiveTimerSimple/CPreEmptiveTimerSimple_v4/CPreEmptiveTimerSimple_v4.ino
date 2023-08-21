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

void handlePreemptive(unsigned long currentMillis,
                      CPreEmptiveTimer *cPreEmptiveTimer,
                      int iPinLed,
                      int iStateUp,
                      int iStateDown) {
  if(cPreEmptiveTimer->timeout(currentMillis)) {
    switch(cPreEmptiveTimer->iState) {
      case 0:
        digitalWrite(iPinLed, HIGH);                 // LED aan
        cPreEmptiveTimer->iState = 1;                // nieuwe status
        cPreEmptiveTimer->setWaitConst(iStateUp);    // wacht ... sec
        break;
      case 1:
        digitalWrite(iPinLed, LOW);                  // LED uit
        cPreEmptiveTimer->iState = 0;                // nieuwe status
        cPreEmptiveTimer->setWaitConst(iStateDown);  // wacht ... sec
        break;
    }
  }
}
                     
void loop() {
  unsigned long currentMillis = millis();

  handlePreemptive(currentMillis, &cPreEmptiveTimer1, PIN_EERSTE_LED, LED1_STATE_UP, LED1_STATE_DOWN);
  handlePreemptive(currentMillis, &cPreEmptiveTimer2, PIN_TWEEDE_LED, LED2_STATE_UP, LED2_STATE_DOWN);
  handlePreemptive(currentMillis, &cPreEmptiveTimer3, PIN_DERDE_LED,  LED3_STATE_UP, LED3_STATE_DOWN);
  handlePreemptive(currentMillis, &cPreEmptiveTimer4, PIN_VIERDE_LED, LED4_STATE_UP, LED4_STATE_DOWN);
}
