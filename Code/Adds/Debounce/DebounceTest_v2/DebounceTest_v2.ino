#include <CPreEmptiveTimer.h>

#define PIN_LED_DEBOUNCED   11
#define PIN_BUTTON          7

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED_DEBOUNCED, OUTPUT);
}

CPreEmptiveTimer cPreEmptiveTimer;
int iDebounceTime = 1000;
bool bState = false;


void loop() {
  unsigned long currentMillis = millis();

  bool bReading = digitalRead(PIN_BUTTON);
  switch(cPreEmptiveTimer.iState) {
    case 0:
      bState = false;
      if(bReading)
        cPreEmptiveTimer.setNewState(1);
      break;

    case 1:
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          cPreEmptiveTimer.setWait(currentMillis, iDebounceTime);
          cPreEmptiveTimer.iSubState = STATE_WAIT;
          break;
        case STATE_WAIT:
          if(!bReading)
            cPreEmptiveTimer.setNewState(0);
          else if(cPreEmptiveTimer.timeout(currentMillis)) {
            cPreEmptiveTimer.setNewState(2);
            bState = true;
          }
          break;
        }
      break;

    case 2:
      if(!bReading)
        cPreEmptiveTimer.setNewState(3);
      break;

    case 3:
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          cPreEmptiveTimer.setWait(currentMillis, iDebounceTime);
          cPreEmptiveTimer.iSubState = STATE_WAIT;
          break;
        case STATE_WAIT:
          if(bReading)
            cPreEmptiveTimer.setNewState(2);
          else if(cPreEmptiveTimer.timeout(currentMillis)) {
            cPreEmptiveTimer.setNewState(0);
            bState = false;
          }
          break;
        }
      break;
  }

  if(bState)
    digitalWrite(PIN_LED_DEBOUNCED,HIGH);
  else
    digitalWrite(PIN_LED_DEBOUNCED,LOW);
}
