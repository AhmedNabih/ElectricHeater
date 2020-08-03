#include "HEATER_Driver.h"

static unsigned char heater_state;

void HEATER_init(tHEATER_State initial_state)
{
    /* Init Tris */
    GPIO_Port_Pin_Init(HEATER_PORT, HEATER_PIN, GPIO_OUT);
    
    heater_state = initial_state;
}

void HEATER_update(void)
{
    GPIO_Set_Port_Pin(HEATER_PORT, HEATER_PIN, heater_state);
}

void HEATER_set_state(tHEATER_State state)
{
    heater_state = state;
}

tHEATER_State HEATER_get_state(void)
{
    tHEATER_State ret = 0;
    
    ret = heater_state;
    
    return ret;
}

void HEATER_toggle(void)
{
    if(heater_state == HEATER_ON)
        heater_state = HEATER_OFF;
    else
        heater_state = HEATER_ON;
}