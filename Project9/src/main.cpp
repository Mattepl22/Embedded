#include "mygpio.h"
#include "myuart.h"

//Definisco INPUT/OUTPUT
#define PIN_LED 2

//Definisco i valori necessari per i timer
#define TIMER_NUMBER 0 //Periferica del timer da usare
#define TIMER_PRESCALER 80//Prescaler del timer per avere 1MHz = 1 tick = 1 microsec
#define TIMER_TRIG 50000 //50ms

#define PW_CHANNEL 0 //Canale della PWM
#define FREQUENCY 5000 //Frequenza della PWM
#define RESOLUTION 8 //Risoluzione PWM

hw_timer_t *timer = NULL;

char rxBuffer[50];

void IRAM_ATTR onTimer();

void setup() {
  Serial.begin(115200);

  uartInit();

  ledcInit(PIN_LED, PW_CHANNEL, FREQUENCY, RESOLUTION);

  //Inizializzo il timer
  timer = timerBegin(TIMER_NUMBER, TIMER_PRESCALER, true);
  //Attacco ISR al timer
  timerAttachInterrupt(timer, &onTimer, true);
  //Setto evento ogni 50ms e ricarico
  timerAlarmWrite(timer, TIMER_TRIG, true);
  //Abilito l'allarme
  timerAlarmEnable(timer);
}

void loop() {

}

void IRAM_ATTR onTimer() {
  bool state = serialRead(rxBuffer);

  if (state){
    if (strcmp(rxBuffer, "on") == 0) {
      setLedIntensity(PW_CHANNEL, 255);
    } else if (strcmp(rxBuffer, "off") == 0) {
      setLedIntensity(PW_CHANNEL, 0);
    } else if (strncmp(rxBuffer, "dim=", 4) == 0) {
      int valTemp = atoi(&rxBuffer[4]);
      if (valTemp > 255) valTemp = 255;
      if (valTemp < 0) valTemp = 0;
      setLedIntensity(PW_CHANNEL, (uint8_t)valTemp);
    }else if (strcmp(rxBuffer, "status") == 0) {
      serialPrint("Jarvis v1.0 status: OK\n");
    } 
  }
}
