#include "mygpio.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2

//Definisco i valori necessari per i timer
#define TIMER_NUMBER 0 //Periferica del timer da usare
#define TIMER_PRESCALER 80//Prescaler del timer per avere 1MHz = 1 tick = 1 microsec
#define TIMER_TRIG 50000 //50ms

hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer();

void setup() {
  Serial.begin(115200);

  uartInit();

  setPinMode(PIN_LED, OUT);

  //Inizializzo il timer
  timer = timerBegin(TIMER_NUMBER, TIMER_PRESCALER, true);
  //Attacco ISR al timer
  timerAttachInterrupt(timer, &onTimer, true);
  //Setto evento ogni 50ms e ricarico
  timerAlarmWrite(timer, TIMER_TRIG, true);
  //Abilito l'allarme
  timerAlarmEnable(timer);
}

void loop() {

}

void IRAM_ATTR onTimer() {
  char c = serialRead();

  if (c == '1') {
    dWrite(PIN_LED, true);
  } else if (c == '0') {
    dWrite(PIN_LED, false);
  }
}
