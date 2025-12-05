#include "myuart.h"

static volatile UART_Regs *myUART0 = (volatile UART_Regs *)0x3FF40000;

// ---- UART ----

void uartInit() {
    //Zittisco Arduino così da poter far vedere a ESP32 cosa scrivo su seriale
    myUART0->int_ena = 0;
}

char IRAM_ATTR uartRead() {
    char c = 0;

    //Leggo myUART0->status e ci applico la maschera
    //Devo leggere i bit 0..7
    //Se il numero è >0 ho qualcosa nel seriale e la leggo con myUART0->fifo
    if ((myUART0->status & 0xFF) > 0) {
        c = myUART0->fifo;
    }

    return c;
}

bool IRAM_ATTR serialRead(char *buffer) {
    static char internalBuffer[50];
    static uint8_t rxIndex = 0;

    uint8_t cnt = myUART0->status & 0xFF;

    while (cnt > 0) {
        char c = myUART0->fifo;

        if (rxIndex >= 49) rxIndex = 0;

        if (c == '\n') {
            internalBuffer[rxIndex] == '\0';

            strcpy(internalBuffer, buffer);

            rxIndex = 0;

            return true;
        } else {
            if (c != '\r') {
                internalBuffer[rxIndex] = c;
                rxIndex++;
            }
        }

        cnt = myUART0->status & 0xFF;
    }
    return false;
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