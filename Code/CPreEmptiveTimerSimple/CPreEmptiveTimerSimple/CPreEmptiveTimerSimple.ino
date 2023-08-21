#include <CPreEmptiveTimer.h>

CPreEmptiveTimer cPreEmptiveTimer1;
CPreEmptiveTimer cPreEmptiveTimer2;
CPreEmptiveTimer cPreEmptiveTimer3;
CPreEmptiveTimer cPreEmptiveTimer4;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  cPreEmptiveTimer1.iState = 0;
  cPreEmptiveTimer1.setWaitConst(1000);  // 1 sec
  cPreEmptiveTimer2.iState = 0;
  cPreEmptiveTimer2.setWaitConst(700);   // 700 ms)
  cPreEmptiveTimer3.iState = 0;
  cPreEmptiveTimer3.setWaitConst(650);   // 650 ms)
  cPreEmptiveTimer4.iState = 0;
  cPreEmptiveTimer4.setWaitConst(1200);   // 1200 ms)
}

void loop() {
  unsigned long currentMillis = millis();

  if(cPreEmptiveTimer1.timeout(currentMillis)) {
    switch(cPreEmptiveTimer1.iState) {
      case 0:
        digitalWrite(10, HIGH);               // LED aan
        cPreEmptiveTimer1.iState = 1;         // nieuwe status
        cPreEmptiveTimer1.setWaitConst(3000); // wacht 1 sec
        break;
      case 1:
        digitalWrite(10, LOW);                // LED uit
        cPreEmptiveTimer1.iState = 0;         // nieuwe status
        cPreEmptiveTimer1.setWaitConst(500); // wacht 1 sec
        break;
    }
  }

  if(cPreEmptiveTimer2.timeout(currentMillis)) {
    switch(cPreEmptiveTimer2.iState) {
      case 0:
        digitalWrite(11, HIGH);             // LED aan
        cPreEmptiveTimer2.iState = 1;        // nieuwe status
        cPreEmptiveTimer2.setWaitConst(700); // wacht 1 sec
        break;
      case 1:
        digitalWrite(11, LOW);              // LED uit
        cPreEmptiveTimer2.iState = 0;        // nieuwe status
        cPreEmptiveTimer2.setWaitConst(700); // wacht 1 sec
        break;
    }
  }

  if(cPreEmptiveTimer3.timeout(currentMillis)) {
    switch(cPreEmptiveTimer3.iState) {
      case 0:
        digitalWrite(6, HIGH);             // LED aan
        cPreEmptiveTimer3.iState = 1;        // nieuwe status
        cPreEmptiveTimer3.setWaitConst(650); // wacht 1 sec
        break;
      case 1:
        digitalWrite(6, LOW);              // LED uit
        cPreEmptiveTimer3.iState = 0;        // nieuwe status
        cPreEmptiveTimer3.setWaitConst(650); // wacht 1 sec
        break;
    }
  }

  if(cPreEmptiveTimer4.timeout(currentMillis)) {
    switch(cPreEmptiveTimer4.iState) {
      case 0:
        digitalWrite(5, HIGH);             // LED aan
        cPreEmptiveTimer4.iState = 1;        // nieuwe status
        cPreEmptiveTimer4.setWaitConst(1200); // wacht 1 sec
        break;
      case 1:
        digitalWrite(5, LOW);              // LED uit
        cPreEmptiveTimer4.iState = 0;        // nieuwe status
        cPreEmptiveTimer4.setWaitConst(1200); // wacht 1 sec
        break;
    }
  }
}
