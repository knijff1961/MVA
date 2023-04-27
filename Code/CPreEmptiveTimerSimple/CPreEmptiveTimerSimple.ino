#include <CPreEmptiveTimer.h>

CPreEmptiveTimer cPreEmtiveTimer1;
CPreEmptiveTimer cPreEmtiveTimer2;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  cPreEmtiveTimer1.iState = 0;
  cPreEmtiveTimer1.setWaitConst(1000);  // 1 sec
  cPreEmtiveTimer2.iState = 0;
  cPreEmtiveTimer2.setWaitConst(700);   // 700 ms)
}

void loop() {
  unsigned long currentMillis = millis();

  if(cPreEmtiveTimer1.timeout(currentMillis)) {
    switch(cPreEmtiveTimer1.iState) {
      case 0:
        digitalWrite(10, HIGH);               // LED aan
        cPreEmtiveTimer1.iState = 1;         // nieuwe status
        cPreEmtiveTimer1.setWaitConst(1000); // wacht 1 sec
        break;
      case 1:
        digitalWrite(10, LOW);                // LED uit
        cPreEmtiveTimer1.iState = 0;         // nieuwe status
        cPreEmtiveTimer1.setWaitConst(1000); // wacht 1 sec
        break;
    }
  }

  if(cPreEmtiveTimer2.timeout(currentMillis)) {
    switch(cPreEmtiveTimer2.iState) {
      case 0:
        digitalWrite(11, HIGH);             // LED aan
        cPreEmtiveTimer2.iState = 1;        // nieuwe status
        cPreEmtiveTimer2.setWaitConst(700); // wacht 1 sec
        break;
      case 1:
        digitalWrite(11, LOW);              // LED uit
        cPreEmtiveTimer2.iState = 0;        // nieuwe status
        cPreEmtiveTimer2.setWaitConst(700); // wacht 1 sec
        break;
    }
  }
}
