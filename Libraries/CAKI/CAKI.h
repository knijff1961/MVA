#ifndef CAKI_H
#define CAKI_H

#include <arduino.h>
#include <CPreEmptiveTimer.h>

#ifndef STATE_INIT
#define STATE_INIT 0
#endif
#ifndef STATE_WAIT
#define STATE_WAIT 1
#endif

class CAKI {
  public:
    CAKI(int iPinRoodLinks,
         int iPinRoodRechts,
         int iPinWit,
         int iWitKnipperFreq,
         int iRoodKnipperFreq);
  
    void go(unsigned long currentMillis, bool bBezet);

    CPreEmptiveTimer cPreEmptiveTimer;
    int iPinRoodLinks;
    int iPinRoodRechts;
    int iPinWit;
    int iWitKnipperFreq;
    int iRoodKnipperFreq;
};
#endif
