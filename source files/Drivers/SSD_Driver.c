#include "SSD_Driver.h"

#define SSD_PORT_STATE PORT_A
#define SSD_PORT_DATA PORT_D
#define SSD_NUMBER 4

typedef struct
{
    tSSD ssd;
    tPin pin;
    tSSD_State state;
    tSSD_Symbol symbol;
    unsigned char is_init;
} tSSD_Info;

static tSSD_Info ssd_info[SSD_NUMBER] =
{
    {SSD_L, PIN_2, SSD_OFF, SSD_NULL, 0},
    {SSD_ML, PIN_3, SSD_OFF, SSD_NULL, 0},
    {SSD_MR, PIN_4, SSD_OFF, SSD_NULL, 0},
    {SSD_R, PIN_5, SSD_OFF, SSD_NULL, 0}
};

static unsigned char lookup_ssd_data[] =
{
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b00000000  // NULL
};

void SSD_init(tSSD ssd, tSSD_State initial_state, tSSD_Symbol initial_symbol)
{
    // Initialize state port
    GPIO_Port_Pin_Init(SSD_PORT_STATE, (tPin)ssd_info[ssd].pin, GPIO_OUT);

    // Initialize data port
    GPIO_Port_Init(SSD_PORT_DATA, GPIO_OUT);

    // Initialize SSD Info
    ssd_info[ssd].is_init = 1;
    ssd_info[ssd].state = initial_state;
    ssd_info[ssd].symbol = initial_symbol;
}

void SSD_update(void)
{
    static tSSD current_ssd = 0;

    /* Turn off all ssd */
    //GPIO_Set_Port_Pin(SSD_PORT_STATE, (tPin)ssd_info[SSD_L].pin, SSD_OFF);
    GPIO_Set_Port_Pin(SSD_PORT_STATE, (tPin)ssd_info[SSD_ML].pin, SSD_OFF);
    GPIO_Set_Port_Pin(SSD_PORT_STATE, (tPin)ssd_info[SSD_MR].pin, SSD_OFF);
    GPIO_Set_Port_Pin(SSD_PORT_STATE, (tPin)ssd_info[SSD_R].pin, SSD_OFF);
     
       
    if(ssd_info[current_ssd].is_init == 1)
    {
        /* Set current ssd output */
        GPIO_Set_Port(SSD_PORT_DATA, lookup_ssd_data[ssd_info[current_ssd].symbol]);
        /* Turn on current ssd */
        GPIO_Set_Port_Pin(SSD_PORT_STATE, (tPin)ssd_info[current_ssd].pin, ssd_info[current_ssd].state);
        //UTIL_DelayMS(5);
    }
    
    current_ssd++;
    if(current_ssd >= SSD_NUMBER)
        current_ssd = 0;
}

void SSD_set_number(unsigned char num)
{
    ssd_info[SSD_L].symbol = (num/1000);
    ssd_info[SSD_ML].symbol = (num%1000)/100;
    ssd_info[SSD_MR].symbol = ((num%1000)%100)/10;
    ssd_info[SSD_R].symbol = (num%10);
}

void SSD_set_state(tSSD ssd, tSSD_State state)
{
    ssd_info[ssd].state = state;
}

void SSD_set_symbol(tSSD ssd, tSSD_Symbol symbol)
{
    ssd_info[ssd].symbol = symbol;
}

tSSD_State SSD_get_state(tSSD ssd)
{
    tSSD_State ret = SSD_OFF;

    ret = ssd_info[ssd].state;

    return ret;
}

tSSD_Symbol SSD_get_symbol(tSSD ssd)
{
    tSSD_Symbol ret = SSD_NULL;

    ret = ssd_info[ssd].symbol;

    return ret;
}

void SSD_toggle_all(void)
{
    tSSD current_ssd = 0;
    for(; current_ssd < SSD_NUMBER; current_ssd++)
    {
        if(ssd_info[current_ssd].state == SSD_ON)
        {
            ssd_info[current_ssd].state = SSD_OFF;
        }
        else
        {
            ssd_info[current_ssd].state = SSD_ON;
        }
    }
}