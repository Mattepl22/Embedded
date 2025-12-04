#include "mygpio.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2
#define PIN_BUTTON 4

void setup() {
  setPinMode(PIN_LED, OUT);
  setPinMode(PIN_BUTTON, IN);
}

void loop() {
  dWrite(PIN_LED, dRead(PIN_BUTTON));
}
