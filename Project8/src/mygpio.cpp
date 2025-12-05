#include "mygpio.h"

static volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;
static volatile UART_Regs *myUART0 = (volatile UART_Regs *)0x3FF40000;

// ---- GPIO ----

void setPinMode(uint8_t PinNumber, bool mode) {
    //Setto il pin come input o output
    if (mode) {
        myGPIO->enable_w1tc = (1 << PinNumber);
    } else {
        myGPIO->enable_w1ts = (1 << PinNumber);
    }
}

void IRAM_ATTR dWrite(uint8_t PinNumber, bool value) {
    //Scrivo sul pin digitale
    if (value) {
        myGPIO->out_w1ts = (1 << PinNumber);
    } else {
        myGPIO ->out_w1tc = (1 << PinNumber);
    }
}

bool dRead(uint8_t PinNumber) {
    //Leggo cosa c'è scritto sul pin
    return (myGPIO->in & (1 << PinNumber)) ? true : false;
}

// ---- UART ----

void uartInit() {
    //Zittisco Arduino così da poter far vedere a ESP32 cosa scrivo su seriale
    myUART0->int_ena = 0;
}

char IRAM_ATTR serialRead() {
    char c = 0;

    //Leggo myUART0->status e ci applico la maschera
    //Devo leggere i bit 0..7
    //Se il numero è >0 ho qualcosa nel seriale e la leggo con myUART0->fifo
    if ((myUART0->status & 0xFF) > 0) {
        c = myUART0->fifo;
    }

    return c;
}

void IRAM_ATTR uartWrite(char c) {
  //Controllo se c'è spazio
  //Estraggo il TX_FIFO_COUNT (bit da 16 a 23)
  //Shift a dx di 16 (16-23 si trovano in 0-7) e maschera (11111111) per pulire sporcizia a sx
    while (((myUART0->status >> 16) & 0xFF) >= 126) { }

    myUART0->fifo = c;
}

void serialPrint(const char *str) {
    while (*str != '\0') {
        uartWrite(*str);
        str++;
    }
}