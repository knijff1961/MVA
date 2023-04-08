#include "CKnipperGloeilicht.h"

CKnipperGloeilicht::CKnipperGloeilicht(Adafruit_PWMServoDriver srituhobby, int iLeft, int iRight, int iSpeed, int iSpeedDelay, int iConstTime) {
  _srituhobby = srituhobby;
  _iLeft = iLeft;
  _iRight = iRight;
  _iSpeed = iSpeed;
  _iSpeedDelay = iSpeedDelay;
  _iConstTime = iConstTime;
}

void CKnipperGloeilicht::CKnipperGloeilicht::begin() {
  _cPreEmtiveTimer.iState = 0;
  _iCurrRightVal = 0;
  _iCurrLeftVal = 0;
  _srituhobby.setPWM(_iLeft,0,0);
  _srituhobby.setPWM(_iRight,0,0);
}

void CKnipperGloeilicht::setState(bool bOn, long ulMillis) {
  if(bOn && _cPreEmtiveTimer.iState == 0)  startKnipper(ulMillis);
  if(!bOn && _cPreEmtiveTimer.iState != 0) stopKnipper(ulMillis);
}

void CKnipperGloeilicht::doLoop(long ulMillis) {
  if(_cPreEmtiveTimer.iState == 0) return;

  if(_cPreEmtiveTimer.timeout(ulMillis))
  {
    switch(_cPreEmtiveTimer.iState) {
      case 1:
        state1(ulMillis);
        break;
      case 2:
        state2(ulMillis);
        break;
      case 3:
        state3(ulMillis);
        break;
      case 4:
        state4(ulMillis);
        break;
      case 5:
        state5(ulMillis);
        break;
      case 6:
        state6(ulMillis);
        break;
        
    }
  }
}

void CKnipperGloeilicht::stopKnipper(long ulMillis) {
  if(_cPreEmtiveTimer.iState==0 || _cPreEmtiveTimer.iState==6) return;
  _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
  _cPreEmtiveTimer.iState = 6; // stop cycle
}
void CKnipperGloeilicht::startKnipper(long ulMillis) {
  if(_cPreEmtiveTimer.iState!=0) return;
  _cPreEmtiveTimer.iState = 1; // start cycle
  _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
}

void CKnipperGloeilicht::displayRightVal() {
  _srituhobby.setPWM(_iLeft,0,_iCurrLeftVal);
  _srituhobby.setPWM(_iRight,0,_iCurrRightVal);
}

void CKnipperGloeilicht::state1(long ulMillis) { // Start with going up only Right light
  _iCurrRightVal += _iSpeed;
  displayRightVal();
  if(_iCurrRightVal>=1023) {
    _iCurrRightVal = 1023;
    _cPreEmtiveTimer.iState = 2;
    _cPreEmtiveTimer.setWait(_iConstTime, ulMillis);
  } else {
    _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
  }
}
void CKnipperGloeilicht::state2(long ulMillis) { // Wait until timeout for rightlight on
  displayRightVal();
  _cPreEmtiveTimer.iState = 3;
  _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
}
void CKnipperGloeilicht::state3(long ulMillis) { // Rightlight goes down, left light goes up
  _iCurrRightVal -= _iSpeed;
  _iCurrLeftVal = 1023 - _iCurrRightVal;
  if(_iCurrRightVal<=0) {
    _iCurrRightVal = 0;
    _iCurrLeftVal = 1023;
    _cPreEmtiveTimer.iState = 4;
    _cPreEmtiveTimer.setWait(_iConstTime, ulMillis);
  } else {
    _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
  }
  displayRightVal();
}
void CKnipperGloeilicht::state4(long ulMillis) { // Wait until timeout for leftlight on
  displayRightVal();
  _cPreEmtiveTimer.iState = 5;
  _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
}
void CKnipperGloeilicht::state5(long ulMillis) { // Rightlight goes up, left light goes down
  _iCurrRightVal += _iSpeed;
  _iCurrLeftVal = 1023 - _iCurrRightVal;
  if(_iCurrRightVal>=1023) {
    _iCurrRightVal = 1023;
    _iCurrLeftVal = 0;
    _cPreEmtiveTimer.iState = 2;
    _cPreEmtiveTimer.setWait(_iConstTime, ulMillis);
  } else {
    _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
  }
  displayRightVal();
}
void CKnipperGloeilicht::state6(long ulMillis) { // tear down state
  _iCurrRightVal -= _iSpeed;
  _iCurrLeftVal  -= _iSpeed;
  if(_iCurrRightVal<0) _iCurrRightVal = 0;
  if(_iCurrLeftVal<0) _iCurrLeftVal = 0;
  if(_iCurrRightVal==0 && _iCurrLeftVal==0) {
    _cPreEmtiveTimer.iState = 0;
    displayRightVal();
    return;
  }
  displayRightVal();
  _cPreEmtiveTimer.setWait(_iSpeedDelay, ulMillis);
}
