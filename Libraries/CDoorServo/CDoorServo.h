#ifndef CDOORSERVO_H
#define CDOORSERVO_H

#include <Adafruit_PWMServoDriver.h>
#include <CPreEmptiveTimer.h>

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class CDoorServo {
  public:
    // Constructor
    CDoorServo(Adafruit_PWMServoDriver srituhobby, int iServoAddr, int servoMIN,int servoMAX, int iOpenStep, int iOpenDelay);

    // Methods:
    void begin();
    void setState(bool bOn, unsigned long ulMillis);
    void doLoop(unsigned long ulMillis);
    int getState();

  private:
    CPreEmptiveTimer _cPreEmtiveTimer;
    Adafruit_PWMServoDriver _srituhobby;
    int iCurrentStep;
    int _servoMIN;
    int _servoMAX;
    int _iServoAddr;
    int _iOpenStep;
    int _iOpenDelay;

    void setPWM(int iVal);
    void startOpen(unsigned long ulMillis);
    void startClose(unsigned long ulMillis);
    void step1(unsigned long ulMillis);
    void step3(unsigned long ulMillis);
    
};
#endif // CDOORSERVO_H
