#include "COOLER_Driver.h"

static unsigned char cooler_state;

void COOLER_init(tCOOLER_State initial_state)
{
    /* Init Tris */
    GPIO_Port_Pin_Init(COOLER_PORT, COOLER_PIN, GPIO_OUT);
    
    cooler_state = initial_state;
}

void COOLER_update(void)
{
    GPIO_Set_Port_Pin(COOLER_PORT, COOLER_PIN, cooler_state);
}

void COOLER_set_state(tCOOLER_State state)
{
    cooler_state = state;
}

tCOOLER_State COOLER_get_state(void)
{
    tCOOLER_State ret = 0;
    
    ret = cooler_state;
    
    return ret;
}

void COOLER_toggle(void)
{
    if(cooler_state == COOLER_ON)
        cooler_state = COOLER_OFF;
    else
        cooler_state = COOLER_ON;
}