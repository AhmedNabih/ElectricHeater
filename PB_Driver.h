#ifndef PUSH_BUTTON_DRIVER_H_INCLUDED
#define PUSH_BUTTON_DRIVER_H_INCLUDED

#include <xc.h>
#include "GPIO_Driver.h"

typedef enum
{
    PB_UP_TEMP,
    PB_DOWN_TEMP,
    PB_ON_OFF_HEATER
} tPB;

typedef enum
{
    PB_RELEASED,
    PB_PRE_PRESSED,
    PB_PRESSED,
    PB_PRE_RELEASED
} tPB_State;

void PB_init(tPB pb, tPB_State initial_state);
void PB_update(void);
tPB_State PB_get_state(tPB pb);

#endif // PUSH_BUTTON_DRIVER_H_INCLUDED
