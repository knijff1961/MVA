#include "CDoorServo.h"


CDoorServo::CDoorServo(Adafruit_PWMServoDriver srituhobby, int iServoAddr, int servoMIN,int servoMAX, int iOpenStep, int iOpenDelay)
{
  _srituhobby = srituhobby;
  _iServoAddr = iServoAddr;
  _iOpenStep =  iOpenStep;
  _servoMIN =  servoMIN;
  _servoMAX =  servoMAX;
  _iOpenDelay = iOpenDelay;
}

void CDoorServo::begin() {
  _cPreEmtiveTimer.iState = 0;
  iCurrentStep = 0;
  _srituhobby.setPWM(_iServoAddr,0,_servoMIN);
}

void CDoorServo::setState(bool bOn, unsigned long ulMillis) {
  //Serial.print("State:");
  //Serial.print(_cPreEmtiveTimer.iState);
  //Serial.print(" bOn:");
  //Serial.print(bOn);
  //Serial.print(" ulMillis:");
  //Serial.println(ulMillis);
  if(bOn && _cPreEmtiveTimer.iState == 0)  startOpen(ulMillis);
  if(!bOn && _cPreEmtiveTimer.iState != 0) startClose(ulMillis);
}

void CDoorServo::doLoop(unsigned long ulMillis) {
  if(_cPreEmtiveTimer.timeout(ulMillis))
  {
    switch(_cPreEmtiveTimer.iState)
    {
      case 1:
        step1(ulMillis);
        break;
      case 3:
        step3(ulMillis);
        break;
    }
  }
}

int CDoorServo::getState() {
  return _cPreEmtiveTimer.iState;
}
void CDoorServo::setPWM(int iVal)
{
  //Serial.print(" iVal:");
  //Serial.println(iVal);
  _srituhobby.setPWM(_iServoAddr,0,iVal);
}

void CDoorServo::startOpen(unsigned long ulMillis) {
  iCurrentStep = _servoMIN;
  if(_cPreEmtiveTimer.iState!=0) return;
  _cPreEmtiveTimer.iState = 1; // start cycle
  _cPreEmtiveTimer.setWait(_iOpenDelay, ulMillis);
}

void CDoorServo::startClose(unsigned long ulMillis) {
  //iCurrentStep = _servoMIN;
  if(_cPreEmtiveTimer.iState==0) return; // stopped already
  if(_cPreEmtiveTimer.iState==3) return; // door is closing
  _cPreEmtiveTimer.iState=3;
  if(_cPreEmtiveTimer.iState==1) return; // door is closing
  _cPreEmtiveTimer.setWait(_iOpenDelay, ulMillis);
}

void CDoorServo::step1(unsigned long ulMillis) {
  iCurrentStep += _iOpenStep;
  if(iCurrentStep >= _servoMAX) {
    iCurrentStep = _servoMAX;
    setPWM(iCurrentStep);
    _cPreEmtiveTimer.setWait(_iOpenDelay, ulMillis);
    _cPreEmtiveTimer.iState = 2;
    return;
  }
  _cPreEmtiveTimer.setWait(_iOpenDelay, ulMillis);
  setPWM(iCurrentStep);
  
}
void CDoorServo::step3(unsigned long ulMillis) {
  iCurrentStep -= _iOpenStep;
  if(iCurrentStep <= _servoMIN) {
    iCurrentStep = _servoMIN;
    setPWM(iCurrentStep);
    _cPreEmtiveTimer.setWait(_iOpenDelay, ulMillis);
    _cPreEmtiveTimer.iState = 0;
    return;
  }
  _cPreEmtiveTimer.setWait(_iOpenDelay, ulMillis);
  setPWM(iCurrentStep);
}
