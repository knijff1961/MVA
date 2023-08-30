#include "CDebounce.h"

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
