#ifndef TIMER0_DRIVER_H_INCLUDED
#define TIMER0_DRIVER_H_INCLUDED

#include "TIMER0_Settings.h"
#include "Interrupt_Setting.h"
#include "main.h"

typedef enum
{
    T0_PRE_2,
    T0_PRE_4,
    T0_PRE_8,
    T0_PRE_16,
    T0_PRE_32,
    T0_PRE_64,
    T0_PRE_128,
    T0_PRE_256,
} tTIMER0_Pre_scaler;

typedef enum
{
    T0_INTERNAL_CLK = 0,
    T0_EXTERNAL_CLK = 1
} tTIMER0_Clock;

typedef enum
{
    T0_INTERRUPT_ON = 1,
    T0_INTERRUPT_OFF = 0
} tTIMER0_interrupt;

typedef enum
{
    T0_ON,
    T0_OFF
} tTIMER0_state;

void TIMER0_init(tTIMER0_Pre_scaler prescaler, tTIMER0_Clock clk);
void TIMER0_start(unsigned int time_ms);
void TIMER0_update(void); // ISR
unsigned char TIMER0_get_count(void);

#endif // TIMER0_DRIVER_H_INCLUDED
