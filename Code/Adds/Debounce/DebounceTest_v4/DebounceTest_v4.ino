#include <CPreEmptiveTimer.h>

#define PIN_LED_DEBOUNCED   11
#define PIN_BUTTON          7


#ifndef CDEBOUNCE_H
#define CDEBOUNCE_H

#include <arduino.h>
#include <CPreEmptiveTimer.h>

#ifndef STATE_INIT
#define STATE_INIT 0
#endif
#ifndef STATE_WAIT
#define STATE_WAIT 1
#endif


class CDebounce {
  public:
    CDebounce(int iPinButton);
    CDebounce(int iPinButton, int iDebounceTime);
  
    void go(unsigned long currentMillis);
    bool getState();
    int  getDebounceTime();
    void setDebounceTime(int iDebounceTime);

  private:
    CPreEmptiveTimer cPreEmptiveTimer;
    int  _iPinButton;
    int  _iDebounceTime = 100;
    bool _bState = false;
};
#endif

CDebounce::CDebounce(int iPinButton) {
  this->_iPinButton = iPinButton;
  pinMode(iPinButton, INPUT);
}

CDebounce::CDebounce(int iPinButton, int iDebounceTime) {
  this->_iPinButton = iPinButton;
  this->_iDebounceTime = iDebounceTime;
  pinMode(iPinButton, INPUT);
}

bool CDebounce::getState() {
  return _bState;
}
int  CDebounce::getDebounceTime() {
  return _iDebounceTime;
}
void CDebounce::setDebounceTime(int iDebounceTime) {
  _iDebounceTime = iDebounceTime;
}

void CDebounce::go(unsigned long currentMillis) {
  bool bReading = digitalRead(_iPinButton);
  switch(cPreEmptiveTimer.iState) {
    case 0:
      if(bReading)
        cPreEmptiveTimer.setNewState(1);
      break;

    case 1:
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          cPreEmptiveTimer.setWait(currentMillis, _iDebounceTime);
          cPreEmptiveTimer.iSubState = STATE_WAIT;
          break;
        case STATE_WAIT:
          if(!bReading)
            cPreEmptiveTimer.setNewState(0);
          else if(cPreEmptiveTimer.timeout(currentMillis)) {
            cPreEmptiveTimer.setNewState(2);
            _bState = true;
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
          cPreEmptiveTimer.setWait(currentMillis, _iDebounceTime);
          cPreEmptiveTimer.iSubState = STATE_WAIT;
          break;
        case STATE_WAIT:
          if(bReading)
            cPreEmptiveTimer.setNewState(2);
          else if(cPreEmptiveTimer.timeout(currentMillis)) {
            cPreEmptiveTimer.setNewState(0);
            _bState = false;
          }
          break;
        }
      break;
  }
}

CDebounce cDebounce = CDebounce(PIN_BUTTON, 1000);

void setup() {
  pinMode(PIN_LED_DEBOUNCED, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  cDebounce.go(currentMillis);
  if(cDebounce.getState())
    digitalWrite(PIN_LED_DEBOUNCED,HIGH);
  else
    digitalWrite(PIN_LED_DEBOUNCED,LOW);
}
