/*
  Simple flash

 This example shows a simple flash light using the
 CPreEmptiveTimer. Led lights are on pin 12 and 13
 
 A CPreEmptiveTimer object has o be made and in the setup
 the status is set to 0 and the timer is started with 1 sec wait time

 code can be found at:
 https://github.com/knijff1961/MVA

 */

#include <CPreEmptiveTimer.h>

CPreEmptiveTimer cPreEmtiveTimer;

#define LIGHT_PIN_1    12
#define LIGHT_PIN_2    13

void setup() {
  Serial.begin(9600);

  while (!Serial); // wait for a serial connection
  cPreEmtiveTimer.iState = 0;

  pinMode(LIGHT_PIN_1, OUTPUT);
  pinMode(LIGHT_PIN_2, OUTPUT);
  
  digitalWrite(LIGHT_PIN_1, HIGH);
  digitalWrite(LIGHT_PIN_2, LOW);

  cPreEmtiveTimer.setWaitConst(1000);
}

void loop() {
  // determine current time (in milliseconds)
  unsigned long currentMillis = millis();

  // wait until timout has occur
  if(cPreEmtiveTimer.timeout(currentMillis)) {
    // a timeout occurred so we have to examen the current state
    // and do our stuff in this state.
    switch(cPreEmtiveTimer.iState) {
      case 0:
        Serial.println("State 0");
        // LIGHT_PIN_1 is on and has to switch off 
        // LIGHT_PIN_2 is off and has to switch on 
        digitalWrite(LIGHT_PIN_1, LOW);
        digitalWrite(LIGHT_PIN_2, HIGH);
        // set state machine to another (next) state
        cPreEmtiveTimer.iState = 1;
        // "reset" the timer so we wait again for 1 second
        cPreEmtiveTimer.setWaitConst(1000);
        // wait for the next timeout.
        break;

      case 1:
        Serial.println("State 1");
        // LIGHT_PIN_2 is on and has to switch off 
        // LIGHT_PIN_1 is off and has to switch on 
        digitalWrite(LIGHT_PIN_1, HIGH);
        digitalWrite(LIGHT_PIN_2, LOW);
        // set state machine to another (next) state
        cPreEmtiveTimer.iState = 0;
        // "reset" the timer so we wait again for 1 second
        cPreEmtiveTimer.setWaitConst(1000);
        // wait for the next timeout.
        break;
    }
  }

  // at this place do other stuff but
  // DON'T USE delay()
  // This code will be executed independant of the timeout.
  // So a second pre emptive state machine can be implmented here.
  // ...
  // delay() is forbidden
}
