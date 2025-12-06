#ifndef MYUART_H
#define MYUART_H

#include <Arduino.h>

// ---- UART ----

typedef struct {
    uint32_t fifo;      //Offset 0x00

    uint32_t int_raw;   //Offset 0x04
    uint32_t int_st;    //Offset 0x08
    uint32_t int_ena;   //Offset 0x0C
    uint32_t int_clr;   //Offset 0x10

    uint32_t clkdiv;    //Offset 0x14
    uint32_t autobaud;  //Offset 0x18

    uint32_t status;    //Offset 0x1C

    uint32_t conf0;     //Offset 0x20
    uint32_t conf1;     //Offset 0x24

    uint32_t lowpulse;  //Offset 0x28
    uint32_t highpulse; //Offset 0x2C
    uint32_t rxd_cnt;   //Offset 0x30
} UART_Regs;

void uartInit();

char uartRead();
bool serialRead(char *buffer);

void uartWrite(char c);
void serialPrint(const char *str);

#endif