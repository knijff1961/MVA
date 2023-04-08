#ifndef CPREEMPTIVETIMER_H
#define CPREEMPTIVETIMER_H

class CPreEmptiveTimer {
  public:
    unsigned int iState;
    unsigned long lastMillis;
    void setWait(unsigned long lMs, unsigned long lTime);
    void setWaitConst(unsigned long lMs);
    bool timeout();
    bool timeout(unsigned long lTime);
};

#endif


