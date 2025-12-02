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
volatile UART_Regs *myUART = (volatile UART_Regs *)0x3FF40000;

void IRAM_ATTR onTimer();
void myPutChar(char c);
void myPrint(const char *str);

void setup() {
  Serial.begin(115200);

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

void myPutChar(char c) {

  //Controllo se c'è spazio
  //Estraggo il TX_FIFO_COUNT (bit da 16 a 23)
  //Shift a dx di 16 (16-23 si trovano in 0-7) e maschera (11111111) per pulire sporcizia a sx
  while (((myUART->status >> 16) & 0xFF) >= 126) {

  }
  myUART->fifo = c;
}

void myPrint(const char *str) {

  while(*str != '\0') {
    myPutChar(*str);
    str++;
  }
}

void IRAM_ATTR onTimer() {
  myPrint("System Status: OK");
}
