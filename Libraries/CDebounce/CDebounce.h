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
