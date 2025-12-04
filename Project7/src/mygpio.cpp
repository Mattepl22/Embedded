#include "mygpio.h"

static volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;
static volatile UART_Regs *myUART0 = (volatile UART_Regs *)0x3FF40000;

void setPinMode(uint8_t PinNumber, bool mode) {
    if (mode) {
        myGPIO->enable_w1tc = (1 << PinNumber);
    } else {
        myGPIO->enable_w1ts = (1 << PinNumber);
    }
}

void dWrite(uint8_t PinNumber, bool value) {
    if (value) {
        myGPIO->out_w1ts = (1 << PinNumber);
    } else {
        myGPIO ->out_w1tc = (1 << PinNumber);
    }
}

bool dRead(uint8_t PinNumber) {
    return (myGPIO->in & (1 << PinNumber)) ? true : false;
}