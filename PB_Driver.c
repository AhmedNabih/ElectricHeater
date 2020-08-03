#include "PB_Driver.h"

#define PB_NUMBER 3
#define PB_SAMPLES_NUMBER 2

#define PB_PRESSED_VOLTAGE  0
#define PB_RELEASED_VOLTAGE  1

typedef struct
{
    tPB pb;
    tPort port;
    tPin pin;
    unsigned char samples[PB_SAMPLES_NUMBER];
    tPB_State state;
    unsigned char is_init;
} tPB_Info;

static tPB_Info pb_info[PB_NUMBER] =
{
    {PB_UP_TEMP, PORT_B, PIN_2,{0,0}, PB_RELEASED, 0},
    {PB_DOWN_TEMP, PORT_B, PIN_1, {0,0}, PB_RELEASED, 0},
    {PB_ON_OFF_HEATER, PORT_B, PIN_0, {0,0}, PB_RELEASED, 0}
};

void PB_init(tPB pb, tPB_State initial_state)
{
    // Initialize port
    GPIO_Port_Pin_Init(pb_info[pb].port, pb_info[pb].pin, GPIO_IN);

    // save PB initialization
    pb_info[pb].is_init = 1;

    // Initial state
    pb_info[pb].state = initial_state;

    // Initialize initial sample
    switch (initial_state)
    {
        case PB_RELEASED:
        case PB_PRE_RELEASED:
            pb_info[pb].samples[0] = PB_RELEASED_VOLTAGE; // 1
            pb_info[pb].samples[1] = PB_RELEASED_VOLTAGE; // 1
            break;
        case PB_PRESSED:
        case PB_PRE_PRESSED:
            pb_info[pb].samples[0] = PB_PRESSED_VOLTAGE; // 0
            pb_info[pb].samples[1] = PB_PRESSED_VOLTAGE; // 0
            break;
    }
}

void PB_update(void)
{
    tPB current_button = 0;
    unsigned char sample_1;
    unsigned char sample_2;
    for(; current_button < PB_NUMBER; current_button++)
    {
        if(pb_info[current_button].is_init == 1)
        {
            sample_1 = pb_info[current_button].samples[1];
            // save 1st sample to cache
            pb_info[current_button].samples[0] = sample_1;

            // save the 2nd sample to cache
            pb_info[current_button].samples[1] = GPIO_Get_Port_Pin(pb_info[current_button].port, pb_info[current_button].pin);

            // update PB state
            sample_1 = pb_info[current_button].samples[0];
            sample_2 = pb_info[current_button].samples[1];
            /*
                Current State	Old Sample	New Sample	Next State
                Released		0			0			Pre-Pressed
                Pre-Pressed 				0			Pressed
                Pressed			1			1			Pre-Released
                Pre-Released				1			Released
            */
            switch(pb_info[current_button].state)
            {
                case PB_RELEASED:
                    if(sample_1 == PB_PRESSED_VOLTAGE && sample_2 == PB_PRESSED_VOLTAGE)
                        pb_info[current_button].state = PB_PRE_PRESSED;
                    break;
                case PB_PRE_PRESSED:
                    if(sample_2 == PB_PRESSED_VOLTAGE)
                        pb_info[current_button].state = PB_PRESSED;
                    break;
                case PB_PRESSED:
                    if(sample_1 == PB_RELEASED_VOLTAGE && sample_2 == PB_RELEASED_VOLTAGE)
                        pb_info[current_button].state = PB_PRE_RELEASED;
                    break;
                case PB_PRE_RELEASED:
                    if(sample_2 == PB_RELEASED_VOLTAGE)
                        pb_info[current_button].state = PB_RELEASED;
                    break;
                default:
                /* Should not be here */
                break;
            }
        }
    }
}

tPB_State PB_get_state(tPB pb)
{
    tPB_State ret = PB_RELEASED;

    ret = pb_info[pb].state;

    return ret;
}
