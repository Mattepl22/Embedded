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

void ledcInit(uint8_t pin, uint8_t pwChannel, uint32_t frequency, uint8_t resolution);
void setLedIntensity(uint8_t pwChannel, uint8_t val);


#endif