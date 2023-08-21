#include "CAKI.h"

CAKI::CAKI(int iPinRoodLinks,
           int iPinRoodRechts,
           int iPinWit,
           int iWitKnipperFreq,
           int iRoodKnipperFreq) {
  this->iPinRoodLinks = iPinRoodLinks;
  this->iPinRoodRechts = iPinRoodRechts;
  this->iPinWit = iPinWit;
  this->iWitKnipperFreq = iWitKnipperFreq;
  this->iRoodKnipperFreq = iRoodKnipperFreq;

  pinMode(iPinRoodLinks, OUTPUT);
  pinMode(iPinRoodRechts, OUTPUT);
  pinMode(iPinWit, OUTPUT);
}

void CAKI::go(unsigned long currentMillis, bool bBezet) {
  switch(cPreEmptiveTimer.iState) {
    case 0: // Witte led aan
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(iPinWit, HIGH);                     // LED aan
          cPreEmptiveTimer.setWait(currentMillis, iWitKnipperFreq); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;         // nieuwe sub status
          break;
        case STATE_WAIT:
          if(bBezet) {
            // Een trein is in het blok
            digitalWrite(iPinWit, LOW);
            cPreEmptiveTimer.setNewState(2);             // de rode leds moeten gaan knipperen
          } else if(cPreEmptiveTimer.timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            cPreEmptiveTimer.setNewState(1);
          }
          break;
      }
      break;
      
    case 1:  // Witte led aan
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(iPinWit, LOW);                      // LED uit
          cPreEmptiveTimer.setWait(currentMillis, iWitKnipperFreq); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;         // nieuwe sub status
          break;
        case STATE_WAIT:
          if(bBezet) {
            // Een trein is in het blok
            cPreEmptiveTimer.setNewState(2);             // de rode leds moeten gaan knipperen
          } else if(cPreEmptiveTimer.timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            cPreEmptiveTimer.setNewState(0);
          }
          break;
        }
      break;

    case 2:  // Links rood aan, rechts rood uit
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(iPinRoodLinks, HIGH);               // linker LED aan
          digitalWrite(iPinRoodRechts, LOW);               // rechter LED uit
          cPreEmptiveTimer.setWait(currentMillis, iRoodKnipperFreq); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;          // nieuwe sub status
          break;
        case STATE_WAIT:
          if(!bBezet) {
            // De trein is uit het blok
            digitalWrite(iPinRoodLinks, LOW);              // rechts is al uit
            cPreEmptiveTimer.setNewState(0);                // state 0: witte led knipperen
          } else if(cPreEmptiveTimer.timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            cPreEmptiveTimer.setNewState(3);
          }
          break;
      }
      break;

    case 3:  // Links rood aan, rechts rood uit
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(iPinRoodLinks, LOW);                // linker LED uit
          digitalWrite(iPinRoodRechts, HIGH);              // rechter LED aan
          cPreEmptiveTimer.setWait(currentMillis, iRoodKnipperFreq); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;          // nieuwe sub status
          break;
        case STATE_WAIT:
          if(!bBezet) {
            // De trein is uit het blok
            digitalWrite(iPinRoodRechts, LOW);             // links is al uit
            cPreEmptiveTimer.setNewState(0);                // state 0: witte led knipperen
          } else if(cPreEmptiveTimer.timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            cPreEmptiveTimer.setNewState(2);
          }
          break;
      }
      break;
  }
}
