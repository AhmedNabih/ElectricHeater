#ifndef LED_DRIVER_H_INCLUDED
#define LED_DRIVER_H_INCLUDED

#include "GPIO_Driver.h"

#define LED_NUMBER 2
#define LED_PORT PORT_B

typedef enum
{
    LED_HEATER, LED_COOLER
} tLED;

typedef enum
{
	LED_OFF = 0,
	LED_ON = 1
} tLED_state;

void LED_init(tLED led, tLED_state initial_state);
void LED_update(void);
void LED_on(tLED led);
void LED_off(tLED led);
tLED_state LED_get_state(tLED led);
void LED_toggle(tLED led);

#endif // LED_DRIVER_H_INCLUDED
