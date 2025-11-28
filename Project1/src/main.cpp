#include "mygpio.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2
#define PIN_BUTTON 4

//Inizializzo la struttura e dico che parte dall'indirizzo scritto
volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;

void setup() {
  //Imposto GPIO2 come OUTPUT
  myGPIO->enable_w1ts = (1 << PIN_LED);

  //Imposto GPIO4 come INPUT
  myGPIO->enable_w1tc = (1 << PIN_BUTTON);
}

void loop() {
  //Leggo lo stato dei registri
  uint32_t regState = myGPIO->in;

  //Condizioni accensione led
  if (regState && (1 << PIN_BUTTON)) {
    //Se dal confronto ho un numero diverso da 0 (TRUE)
    myGPIO->out_w1ts = (1 << PIN_LED); //Accendo il led -> Alzo il bit corrispondente
  } else {
    //Se dal confronto ho 0 (FALSE)
    myGPIO->out_w1tc = (1 << PIN_LED); //Spengo il led -> Abbasso il bit corrispondente
  }
}
