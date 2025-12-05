#ifndef MYGPIO_H
#define MYGPIO_H

#include <Arduino.h>

#define IN true
#define OUT false

// ---- GPIO ----
typedef struct {
    uint32_t bt_select;     //Offset 0x00
    uint32_t out;           //Offset 0x04
    uint32_t out_w1ts;      //Offset 0x08
    uint32_t out_w1tc;      //Offset 0x0C

    uint32_t out1;          //Offset 0x10
    uint32_t out1_w1ts;     //Offset 0x14
    uint32_t out1_w1tc;     //Offset 0x18

    uint32_t unused_1;      //Offset 0x1C

    uint32_t enable;        //Offset 0x20
    uint32_t enable_w1ts;   //Offset 0x24
    uint32_t enable_w1tc;   //Offset 0x28

    uint32_t enable1;       //Offset 0x2C
    uint32_t enable1_w1ts;  //Offset 0x30
    uint32_t enable1_w1tc;  //Offset 0x34

    uint32_t strap;         //Offset 0x38

    uint32_t in;            //Offset 0x3C
    uint32_t in1;           //Offset 0x40    
} GPIO_Regs;

void setPinMode(uint8_t PinNumber, bool mode);
void dWrite(uint8_t PinNumber, bool value);
bool dRead(uint8_t PinNumber);

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
char serialRead();
void uartWrite(char c);
void serialPrint(const char *str);


#endif