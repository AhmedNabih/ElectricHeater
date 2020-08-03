#include "Interrupt.h"

void __interrupt() interrupty()
{
    if(PORTB0_GET_INTERRUPT_FLAG() == 1)
    {
        PORTB0_SET_INTERRUPT_FLAG(0);
    }
    else if(TIMER0_GET_INTERRUPT_FLAG() == 1)
    {
        TIMER0_update();
    }
}
