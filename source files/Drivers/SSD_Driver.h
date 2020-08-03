#ifndef SSD_DRIVER_H_INCLUDED
#define SSD_DRIVER_H_INCLUDED

#include "GPIO_Driver.h"
#include "utilities.h"

typedef enum
{
    SSD_L,
    SSD_ML,
    SSD_MR,
    SSD_R
} tSSD;

typedef enum
{
    SSD_OFF = 0,
    SSD_ON = 1
} tSSD_State;

typedef enum
{
   SSD_0, SSD_1, SSD_2, SSD_3,
   SSD_4, SSD_5, SSD_6, SSD_7,
   SSD_8, SSD_9, SSD_NULL
} tSSD_Symbol;

void SSD_init(tSSD ssd, tSSD_State initial_state, tSSD_Symbol initial_symbol);
void SSD_update(void);
void SSD_set_number(unsigned char num);
void SSD_set_state(tSSD ssd, tSSD_State state);
void SSD_set_symbol(tSSD ssd, tSSD_Symbol symbol);
tSSD_State SSD_get_state(tSSD ssd);
tSSD_Symbol SSD_get_symbol(tSSD ssd);
void SSD_toggle_all(void);


#endif // SSD_DRIVER_H_INCLUDED
