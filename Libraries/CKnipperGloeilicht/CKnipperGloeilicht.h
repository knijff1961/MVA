#ifndef CKNIPPERGLOEILICHT_H
#define CKNIPPERGLOEILICHT_H

#include <Adafruit_PWMServoDriver.h>
#include <CPreEmptiveTimer.h>

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class CKnipperGloeilicht {
  public:
    // Constructor
    CKnipperGloeilicht(Adafruit_PWMServoDriver srituhobby, int iLeft, int iRight, int iSpeed, int iSpeedDelay, int iConstTime);

    // Methods:
    void begin();
    void setState(bool bOn, long ulMillis);
    void doLoop(long ulMillis);

  private:
    Adafruit_PWMServoDriver _srituhobby;
    CPreEmptiveTimer _cPreEmtiveTimer;

    int _iLeft;
    int _iRight;

    int _iSpeed;   // time per step to get light up;
    int _iConstTime; // time thate light stays on/off;
    int _iSpeedDelay;

    int _iCurrRightVal;
    int _iCurrLeftVal;

    void stopKnipper(long ulMillis);
    void startKnipper(long ulMillis);
    void displayRightVal();
    void state1(long ulMillis);
    void state2(long ulMillis);
    void state3(long ulMillis);
    void state4(long ulMillis);
    void state5(long ulMillis);
    void state6(long ulMillis);
};
#endif // CKNIPPERGLOEILICHT_H
