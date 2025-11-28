#include "mygpio.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2
#define PIN_BUTTON 4

#define DELAY_TIME 200 //Tempo di delay tra una pressione e la successiva

//Inizializzo la struttura e dico che parte dall'indirizzo scritto
volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;

void IRAM_ATTR onButtonPress();

void setup() {
  //Imposto GPIO2 come OUTPUT
  myGPIO->enable_w1ts = (1 << PIN_LED);

  //Imposto GPIO4 come INPUT
  myGPIO->enable_w1tc = (1 << PIN_BUTTON);

  //Alla pressione del tasto genero un interrupt che mi cambia lo state
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), onButtonPress, RISING); 
}

void loop() {

}

void IRAM_ATTR onButtonPress() {

  static volatile unsigned long startTime = 0; //Variabile per il debounce
  static volatile byte state = LOW; //Variabile di stato

  if (millis() - startTime > DELAY_TIME) {
    state = !state;
    
    if (state) {
      myGPIO->out_w1ts = (1 << PIN_LED); //Accendo il led -> Alzo il bit corrispondente
    } else {
      myGPIO->out_w1tc = (1 << PIN_LED); //Spengo il led -> Abbasso il bit corrispondente
    }

    startTime = millis();
  }
}
