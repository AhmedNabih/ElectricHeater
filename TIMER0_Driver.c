#include "TIMER0_Driver.h"

static tTIMER0_Pre_scaler current_prescaler;
static tTIMER0_Clock current_clk;
static unsigned char initial_cnt;

void TIMER0_init(tTIMER0_Pre_scaler prescaler, tTIMER0_Clock clk)
{
    current_prescaler = prescaler;
    current_clk = clk;

    TIMER0_INTERRUPT_ENABLE(T0_INTERRUPT_OFF);
    TIMER0_CLEAR_INTERRUPT_FLAG();
    TIMER0_SET_STATE(T0_OFF);
    TIMER0_INIT_PRESCALER();
    TIMER0_SET_PRESCALER(prescaler_info[current_prescaler].bit_value);
}

void TIMER0_start(unsigned int time_ms)
{
    initial_cnt = TIMER0_GET_INITIAL_CNT(time_ms, prescaler_info[current_prescaler].factor);
    //TIMER0_COUNT_RISING_EDGE();
    TIMER0_SELECT_CLOCK(current_clk);
    TIMER0_CLEAR_INTERRUPT_FLAG();
    TIMER0_INTERRUPT_ENABLE(T0_INTERRUPT_ON);
    GLOBAL_INTERRUPT_ENABLE(1);
    TIMER0_SET_STATE(T0_ON);
    TIMER0_SET_INITIAL_CNT(time_ms, prescaler_info[current_prescaler].factor);
}

unsigned char TIMER0_get_count(void)
{
    unsigned char ret = 0, cnt;
    
    cnt = TIMER0_GET_CNT();
    ret = cnt;
    
    return ret;
}

void TIMER0_update(void) // ISR
{   
    flag = TRUE;
    
    TIMER0_CLEAR_INTERRUPT_FLAG();
    TIMER0_SET_INITIAL_CNT(TICK_MS, prescaler_info[current_prescaler].factor);
}
