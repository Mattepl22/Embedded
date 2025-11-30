#include "mygpio.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2
#define PIN_BUTTON 4

#define DELAY_TIME 200 //Tempo di delay tra una pressione e la successiva
#define TIMER_NUMBER 0 //Periferica del timer da usare
#define PRESCALER 80 //Prescaler del timer per avere 1MHz = 1 tick = 1microsec 
#define TIME_TRIG 500000 //500ms = 500.000 microsec

hw_timer_t *timer = NULL;

//Inizializzo la struttura e dico che parte dall'indirizzo scritto
volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;

void IRAM_ATTR onTimer();

void setup() {
  //Imposto GPIO2 come OUTPUT
  myGPIO->enable_w1ts = (1 << PIN_LED);

  //Imposto GPIO4 come INPUT
  myGPIO->enable_w1tc = (1 << PIN_BUTTON);

  //Inizializzazione del timer
  timer = timerBegin(TIMER_NUMBER, PRESCALER, true);
  //Attacco l'ISR al timer
  timerAttachInterrupt(timer, &onTimer, true); 
  //Setto l'evento ogni 500ms e ricarico
  timerAlarmWrite(timer, TIME_TRIG, true);
  //Abilito l'allarme
  timerAlarmEnable(timer); 
}

void loop() {

}

void IRAM_ATTR onTimer() {
  static volatile uint8_t state = 0; //Variabile di stato
  
  state ^= 1;
  
  (state) ? (myGPIO->out_w1ts = (1 << PIN_LED)) : (myGPIO->out_w1tc = (1 << PIN_LED));
}
