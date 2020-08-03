#ifndef COOLER_DRIVER_H
#define	COOLER_DRIVER_H

#include "GPIO_Driver.h"

#define COOLER_PORT PORT_C
#define COOLER_PIN  PIN_2

typedef enum
{
    COOLER_OFF,
    COOLER_ON
} tCOOLER_State;

void COOLER_init(tCOOLER_State initial_state);
void COOLER_update(void);
void COOLER_set_state(tCOOLER_State state);
tCOOLER_State COOLER_get_state(void);
void COOLER_toggle(void);

#endif	/* COOLER_DRIVER_H */

