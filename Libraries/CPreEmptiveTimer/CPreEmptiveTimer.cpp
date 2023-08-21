#include "Arduino.h"
#include <CPreEmptiveTimer.h>

CPreEmptiveTimer::CPreEmptiveTimer() {
  iState = 0;
  iSubState = 0;
}

// set the wait time to wait for the timeout;
//   unsigned long lTime
//     Start time (most of the time: current time derived from millis()
//   unsigned long lMs
//     Offset to the start time; added together will result in the timeout - time
// NOTE: Most of the time, this is the only wait setting used.
//       See setWaitConst for a more accurate setting of the timeout but that is most of the time overdone.
void CPreEmptiveTimer::setWait(unsigned long lMs, unsigned long lTime) {
  lastMillis = lTime + lMs;
}

// Set the wait time for the timeout exactly after a preivious timeout.
// This is only needed when a new timeout has to be set which is exactly an offset of the last timeout setting (not timeout action)
// Then a risk is that when lMs is very short, the timeout() will be immeditaly true and, when using long state transitions, the
// timeout() will always be true.
//   unsigned long lMs
//     Offset to the last expected timeout; added together will result in the timeout - lastMillis
// NOTE: current time (from miliis()) is equal of higher then lastMillis
void CPreEmptiveTimer::setWaitConst(unsigned long lMs) {
  lastMillis = lastMillis + lMs;
}

// Test if a timeout has occur
//    True: a timeout has occur
//    False: no timeout yet
// NOTE: this routine calles millis(). It is a better practice to get millis() at the loop() entrance and use the next timout method.
bool CPreEmptiveTimer::timeout() {
      long lTime = millis();
      if(lTime>lastMillis)
          return true;
      return false;
}

// Test if a timeout has occur
//    True: a timeout has occur
//    False: no timeout yet
//  unsigned long lTime
//     The time to refer the timeout state.
//     This value is previously derived from the 
bool CPreEmptiveTimer::timeout(unsigned long lTime) {
      if(lTime>lastMillis)
          return true;
      return false;
}

