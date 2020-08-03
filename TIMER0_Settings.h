#ifndef TIMER0_SETTINGS_H_INCLUDED
#define TIMER0_SETTINGS_H_INCLUDED

#include <xc.h>

#define TIMER0_MAX_PRESCALER_CONFIG 8
#define TIMER0_MAX_COUNT 256

/**********************************************
    Timer0
        - Flag: TMR0IE, Enable: 1, Disable: 0
        - Flag: TMR0IF, Interrupt Occur: 1, No Interrupt Occur: 0, Notes: must be cleared after each interrupt
        - Flag: PSA, Set to Timer0: 0, Set to WDT: 1
        - Flag: PS2, PS1, PS0, set to pre-scaler from 0-7
        - Flag: T0CS, OSC Clock Select: 0, External Clock Select: 1
        - Flag: T0SE, Count Rising Edge: 0, Count Falling Edge: 1
        - Flag: TMR0, initial count 8 bit register, Notes: Timer0 is configured for 8 MHZ OSC
**********************************************/

#define TIMER0_INTERRUPT_ENABLE(X)      TMR0IE = X
#define TIMER0_CLEAR_INTERRUPT_FLAG()   TMR0IF = 0
#define TIMER0_GET_INTERRUPT_FLAG()     TMR0IF
#define TIMER0_INIT_PRESCALER()         PSA = 0
#define TIMER0_SET_PRESCALER(X)         PS2 = (X&0x4) >> 2;\
                                        PS1 = (X&0x2) >> 1;\
                                        PS0 = (X&0x1);
#define TIMER0_SELECT_CLOCK(X)          T0CS = X
#define TIMER0_COUNT_RISING_EDGE()      T0SE = 0
#define TIMER0_COUNT_FALLING_EDGE()     T0SE = 1
#define TIMER0_SET_STATE(X)             T0CS = X

#define TIMER0_SET_INITIAL_CNT(TIME_MS, PS_FACTOR)  (TMR0 = TIMER0_MAX_COUNT - PS_FACTOR * TIME_MS)
#define TIMER0_GET_CNT()                            (TMR0)
#define TIMER0_GET_INITIAL_CNT(TIME_MS, PS_FACTOR)  (TIMER0_MAX_COUNT - PS_FACTOR * TIME_MS)

typedef struct
{
    unsigned short factor;
    unsigned short pre_scaler;
    unsigned char bit_value;
} tTimer0_prescaler_info;

static tTimer0_prescaler_info prescaler_info[TIMER0_MAX_PRESCALER_CONFIG] =
{
    {1000, 2, 0},
    {500, 4, 1},
    {250, 8, 2},
    {125, 16, 3},
    {62, 32, 4},
    {31, 64, 5},
    {15, 128, 6},
    {7, 256, 7},
};

#endif // TIMER0_SETTINGS_H_INCLUDED
