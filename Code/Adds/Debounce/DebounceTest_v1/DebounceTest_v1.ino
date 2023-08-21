#include <CPreEmptiveTimer.h>

#define PIN_LED_BOUNCED_UP  11
#define PIN_BUTTON          7

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED_BOUNCED_UP, OUTPUT);
}

int iLastBounceState = LOW;
int iLastDebounceState = LOW;
int iLastReading = LOW;

void bounce(int reading) {
  
  if(iLastReading!=reading) {
    iLastReading = reading;
    if(reading==HIGH) {
      if(iLastBounceState==LOW) {
        iLastBounceState=HIGH;
      } else {
        iLastBounceState=LOW;
      }
      digitalWrite(PIN_LED_BOUNCED_UP, iLastBounceState);
    }
  }
}

void loop() {
  int reading = digitalRead(PIN_BUTTON);
  bounce(reading);
}
