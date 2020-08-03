#ifndef GPIO_DRIVER_H_INCLUDED
#define GPIO_DRIVER_H_INCLUDED

#include <xc.h>

typedef enum
{
	PORT_A, PORT_B, PORT_C, PORT_D, PORT_E
} tPort;

typedef enum
{
    PIN_0, PIN_1, PIN_2, PIN_3, 
    PIN_4, PIN_5, PIN_6, PIN_7
} tPin;

typedef enum
{
    GPIO_OUT,
    GPIO_IN
} tPort_Direction;

typedef enum
{
    PIN_OFF, 
    PIN_ON
} tPin_State;

void GPIO_Port_Pin_Init(tPort port, tPin pin, tPort_Direction dir);
void GPIO_Port_Init(tPort port, tPort_Direction dir);
void GPIO_Update(void);
void GPIO_Set_Port_Pin(tPort port, tPin pin, tPin_State port_state);
void GPIO_Set_Port(tPort port, unsigned char state);
tPin_State GPIO_Get_Port_Pin(tPort port, tPin pin);

#endif // GPIO_DRIVER_H_INCLUDED
