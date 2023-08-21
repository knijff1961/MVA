#include <CPreEmptiveTimer.h>

#define PIN_ROOD_LINKS_1  11
#define PIN_ROOD_RECHTS_1 10
#define PIN_WIT_1         6
#define PIN_BUTTON_1      5

#define WIT_KNIPPER_FREQ   750     // 3/4 sec
#define ROOD_KNIPPER_FREQ  500     // 2x een halve sec

CPreEmptiveTimer cPreEmptiveTimer1;

void setup() {
  pinMode(PIN_ROOD_LINKS_1, OUTPUT);
  pinMode(PIN_ROOD_RECHTS_1, OUTPUT);
  pinMode(PIN_WIT_1, OUTPUT);
  pinMode(PIN_BUTTON_1, INPUT);
}

void AKI_go(unsigned long currentMillis,
        CPreEmptiveTimer *pPreEmptiveTimer,
        int iPinRoodLinks,
        int iPinRoodRechts,
        int iPinWit,
        int iButtonPin,
        int iWitKnipperFreq,
        int iRoodKnippreFreq) {
  
  int val = digitalRead(iButtonPin);
  
  switch(pPreEmptiveTimer->iState) {
    case 0: // Witte led aan
      switch(pPreEmptiveTimer->iSubState) {
        case STATE_INIT:
          digitalWrite(iPinWit, HIGH);                     // LED aan
          pPreEmptiveTimer->setWait(currentMillis, iWitKnipperFreq); // wacht ... sec
          pPreEmptiveTimer->iSubState = STATE_WAIT;         // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==HIGH) {
            // Een trein is in het blok
            digitalWrite(iPinWit, LOW);
            pPreEmptiveTimer->setNewState(2);             // de rode leds moeten gaan knipperen
          } else if(pPreEmptiveTimer->timeout(currentMillis)) {   // Is een timeout opgetreden?
            pPreEmptiveTimer->setNewState(1);
          }
          break;
      }
      break;
      
    case 1:  // Witte led aan
      switch(pPreEmptiveTimer->iSubState) {
        case STATE_INIT:
          digitalWrite(iPinWit, LOW);                      // LED uit
          pPreEmptiveTimer->setWait(currentMillis, iWitKnipperFreq); // wacht ... sec
          pPreEmptiveTimer->iSubState = STATE_WAIT;         // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==HIGH) {
            // Een trein is in het blok
            // digitalWrite(iPinWit, LOW); is niet nodig; witte led is al uit
            pPreEmptiveTimer->setNewState(2);             // de rode leds moeten gaan knipperen
          } else if(pPreEmptiveTimer->timeout(currentMillis)) {   // Is een timeout opgetreden?
            pPreEmptiveTimer->setNewState(0);
          }
          break;
        }
      break;

    case 2:  // Links rood aan, rechts rood uit
      switch(pPreEmptiveTimer->iSubState) {
        case STATE_INIT:
          digitalWrite(iPinRoodLinks, HIGH);               // linker LED aan
          digitalWrite(iPinRoodRechts, LOW);               // rechter LED uit
          pPreEmptiveTimer->setWait(currentMillis, iRoodKnippreFreq); // wacht ... sec
          pPreEmptiveTimer->iSubState = STATE_WAIT;          // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==LOW) {
            // De trein is uit het blok
            digitalWrite(iPinRoodLinks, LOW);              // rechts is al uit
            pPreEmptiveTimer->setNewState(0);                // state 0: witte led knipperen
          } else if(pPreEmptiveTimer->timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            pPreEmptiveTimer->setNewState(3);
          }
          break;
      }
      break;

    case 3:  // Links rood aan, rechts rood uit
      switch(pPreEmptiveTimer->iSubState) {
        case STATE_INIT:
          digitalWrite(iPinRoodLinks, LOW);                // linker LED uit
          digitalWrite(iPinRoodRechts, HIGH);              // rechter LED aan
          pPreEmptiveTimer->setWait(currentMillis, iRoodKnippreFreq); // wacht ... sec
          pPreEmptiveTimer->iSubState = STATE_WAIT;          // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==LOW) {
            // De trein is uit het blok
            digitalWrite(iPinRoodRechts, LOW);             // links is al uit
            pPreEmptiveTimer->setNewState(0);                // state 0: witte led knipperen
          } else if(pPreEmptiveTimer->timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            pPreEmptiveTimer->setNewState(2);
          }
          break;
      }
      break;
  }
}


void loop() {
  unsigned long currentMillis = millis();
  AKI_go(currentMillis, &cPreEmptiveTimer1, PIN_ROOD_LINKS_1, PIN_ROOD_RECHTS_1,
         PIN_WIT_1, PIN_BUTTON_1, WIT_KNIPPER_FREQ, ROOD_KNIPPER_FREQ);
}
