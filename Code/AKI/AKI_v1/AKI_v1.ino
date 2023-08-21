#include <CPreEmptiveTimer.h>

#define PIN_ROOD_LINKS  11
#define PIN_ROOD_RECHTS 10
#define PIN_WIT         6
#define PIN_BUTTON      5

#define WIT_KNIPPER_FREQ   750     // 3/4 sec
#define ROOD_KNIPPER_FREQ  500     // 2x een halve sec

CPreEmptiveTimer cPreEmptiveTimer;

void setup() {
  pinMode(PIN_ROOD_LINKS, OUTPUT);
  pinMode(PIN_ROOD_RECHTS, OUTPUT);
  pinMode(PIN_WIT, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

}
                     
void loop() {
  unsigned long currentMillis = millis();
  int val = digitalRead(PIN_BUTTON);
  
  switch(cPreEmptiveTimer.iState) {
    case 0: // Witte led aan
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(PIN_WIT, HIGH);                     // LED aan
          cPreEmptiveTimer.setWait(currentMillis, WIT_KNIPPER_FREQ); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;         // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==HIGH) {
            // Een trein is in het blok
            digitalWrite(PIN_WIT, LOW);
            cPreEmptiveTimer.setNewState(2);             // de rode leds moeten gaan knipperen
          } else if(cPreEmptiveTimer.timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            // setNewState() zet automatisch iSubState = STATE_INIT
            cPreEmptiveTimer.setNewState(1);
          }
          break;
      }
      break;
      
    case 1:  // Witte led aan
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(PIN_WIT, LOW);                      // LED uit
          cPreEmptiveTimer.setWait(currentMillis, WIT_KNIPPER_FREQ); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;         // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==HIGH) {
            // Een trein is in het blok
            // digitalWrite(PIN_WIT, LOW); is niet nodig; witte led is al uit
            cPreEmptiveTimer.setNewState(2);             // de rode leds moeten gaan knipperen
          } else if(cPreEmptiveTimer.timeout(currentMillis)) {   // Is een timeout opgetreden?
            // Zet de nieuwe state
            // setNewState() zet automatisch iSubState = STATE_INIT
            cPreEmptiveTimer.setNewState(0);
          }
          break;
        }
      break;

    case 2:  // Links rood aan, rechts rood uit
      switch(cPreEmptiveTimer.iSubState) {
        case STATE_INIT:
          digitalWrite(PIN_ROOD_LINKS, HIGH);               // linker LED aan
          digitalWrite(PIN_ROOD_RECHTS, LOW);               // rechter LED uit
          cPreEmptiveTimer.setWait(currentMillis, ROOD_KNIPPER_FREQ); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;          // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==LOW) {
            // De trein is uit het blok
            digitalWrite(PIN_ROOD_LINKS, LOW);              // rechts is al uit
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
          digitalWrite(PIN_ROOD_LINKS, LOW);                // linker LED uit
          digitalWrite(PIN_ROOD_RECHTS, HIGH);              // rechter LED aan
          cPreEmptiveTimer.setWait(currentMillis, ROOD_KNIPPER_FREQ); // wacht ... sec
          cPreEmptiveTimer.iSubState = STATE_WAIT;          // nieuwe sub status
          break;
        case STATE_WAIT:
          if(val==LOW) {
            // De trein is uit het blok
            digitalWrite(PIN_ROOD_RECHTS, LOW);             // links is al uit
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
