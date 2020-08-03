#ifndef HEATER_DRIVER_H
#define	HEATER_DRIVER_H

#include "GPIO_Driver.h"

#define HEATER_PORT PORT_C
#define HEATER_PIN  PIN_5

typedef enum
{
    HEATER_OFF,
    HEATER_ON
} tHEATER_State;

void HEATER_init(tHEATER_State initial_state);
void HEATER_update(void);
void HEATER_set_state(tHEATER_State state);
tHEATER_State HEATER_get_state(void);
void HEATER_toggle(void);

#endif	/* HEATER_DRIVER_H */

