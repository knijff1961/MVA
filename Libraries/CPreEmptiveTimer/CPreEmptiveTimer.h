#ifndef CPREEMPTIVETIMER_H
#define CPREEMPTIVETIMER_H

#ifndef STATE_INIT
#define STATE_INIT 0
#endif
#ifndef STATE_WAIT
#define STATE_WAIT 1
#endif

class CPreEmptiveTimer {
  public:
    CPreEmptiveTimer();
    CPreEmptiveTimer(unsigned long lMs);
    CPreEmptiveTimer(unsigned long lMs, unsigned long lTime);
	
    unsigned int iState;
    unsigned int iSubState;
    unsigned long lastMillis;
    void setWait(unsigned long lMs, unsigned long lTime);
    void setWaitConst(unsigned long lMs);
	void setNewState(int iNewState, int iNewSubState = 0);
    bool timeout();
    bool timeout(unsigned long lTime);
};

#endif
