#include "Arduino.h"
#include <CPreEmptiveTimer.h>

// set the wait time to wait for the timeout;
//   unsigned long lTime
//     Start time (most of the time: current time derived from millis()
//   unsigned long lMs
//     Offset to the start time; added together will result in the timeout - time
void CPreEmptiveTimer::setWait(unsigned long lMs, unsigned long lTime) {
  lastMillis = lTime + lMs;
}

void CPreEmptiveTimer::setWaitConst(unsigned long lMs) {
  lastMillis = lastMillis + lMs;
}

bool CPreEmptiveTimer::timeout() {
      long lTime = millis();
      if(lTime>lastMillis)
          return true;
      return false;
}

// 
bool CPreEmptiveTimer::timeout(unsigned long lTime) {
      if(lTime>lastMillis)
          return true;
      return false;
}

