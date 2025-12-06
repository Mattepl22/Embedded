#include "mygpio.h"

static volatile GPIO_Regs *myGPIO = (volatile GPIO_Regs *)0x3FF44000;

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

void ledcInit(uint8_t pin, uint8_t pwChannel, uint32_t frequency, uint8_t resolution) {
    ledcSetup(pwChannel, frequency, resolution);
    ledcAttachPin(pin, pwChannel);
}

void IRAM_ATTR setLedIntensity(uint8_t pwChannel, uint8_t val) {
    if (val > 255) val = 255;
    if (val < 0) val = 0;

    ledcWrite(pwChannel, val);
}