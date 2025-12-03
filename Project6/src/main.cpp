#include "mygpio.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2
#define PIN_BUTTON 4

#define DELAY_TIME 200 //Tempo di delay tra una pressione e la successiva
#define TIMER_NUMBER 0 //Periferica del timer da usare
#define PRESCALER 80 //Prescaler del timer per avere 1MHz = 1 tick = 1microsec 
#define TIME_TRIG 50000 //500ms = 500.000 microsec

hw_timer_t *timer = NULL;

//Inizializzo la struttura e dico che parte dall'indirizzo scritto
volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;
volatile UART_Regs *myUART = (volatile UART_Regs *)0x3FF40000;

void IRAM_ATTR onTimer();
char serialRead();

void setup() {
  Serial.begin(115200);

  myUART->int_ena = 0;

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

char serialRead() {
  char c = 0;

  if ((myUART->status & 0xFF) > 0) {
    c = myUART->fifo;
  }
  return c;
}

void IRAM_ATTR onTimer() {
  char c = serialRead();

  if (c == '1') {
    myGPIO->out_w1ts = (1 << PIN_LED);
  } else if (c == '0') {
    myGPIO->out_w1tc = (1 << PIN_LED);
  }
}
