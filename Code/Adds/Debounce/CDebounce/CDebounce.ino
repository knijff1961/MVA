#include <CPreEmptiveTimer.h>
#include <CDebounce.h>

#define PIN_LED_DEBOUNCED   10
#define PIN_BUTTON          7

//CDebounce cDebounce = CDebounce(PIN_BUTTON);
CDebounce cDebounce = CDebounce(PIN_BUTTON, 1000);

void setup() {
  pinMode(PIN_LED_DEBOUNCED, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  cDebounce.go(currentMillis);
  if(cDebounce.getState())
    digitalWrite(PIN_LED_DEBOUNCED,HIGH);
  else
    digitalWrite(PIN_LED_DEBOUNCED,LOW);
}
