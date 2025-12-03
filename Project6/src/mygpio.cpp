#include "mygpio.h"

static volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;
static volatile UART_Regs myUART0 = (volatile UART_Regs *)0x3FF40000;

void setPinMode(uint8_t PinNumber, bool mode) {
    
}