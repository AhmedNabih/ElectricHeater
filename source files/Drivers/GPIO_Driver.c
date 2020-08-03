#include "GPIO_Driver.h"

#define MAX_PIN_PORT_A 6
#define MAX_PIN_PORT_B 8
#define MAX_PIN_PORT_C 8
#define MAX_PIN_PORT_D 8
#define MAX_PIN_PORT_E 3

#define REG_SET_BIT(REG, BIT, DATA)	(REG = ((REG & (~(1<<BIT)))|(DATA<<BIT)))
#define REG_GET_BIT(REG, BIT) ((REG & (1<<BIT))>>BIT)

void GPIO_Port_Pin_Init(tPort port, tPin pin, tPort_Direction dir)
{
    switch(port)
    {
        case PORT_A:
            if(pin < MAX_PIN_PORT_A)
                REG_SET_BIT(TRISA, pin, dir);
            break;
        case PORT_B:
            if(pin < MAX_PIN_PORT_B)
                REG_SET_BIT(TRISB, pin, dir);
            break;
        case PORT_C:
            if(pin < MAX_PIN_PORT_C)
                REG_SET_BIT(TRISC, pin, dir);
            break;
        case PORT_D:
            if(pin < MAX_PIN_PORT_D)
                REG_SET_BIT(TRISD, pin, dir);
            break;
        case PORT_E:
            if(pin < MAX_PIN_PORT_E)
                REG_SET_BIT(TRISE, pin, dir);
            break;
        default:
			/* Should not be here */
			break;
    }
}

void GPIO_Port_Init(tPort port, tPort_Direction dir)
{
    unsigned char pin;
    unsigned char max_pin = 0;
    switch(port)
    {
        case PORT_A:
            max_pin = MAX_PIN_PORT_A;
            break;
        case PORT_B:
            max_pin = MAX_PIN_PORT_B;
            break;
        case PORT_C:
            max_pin = MAX_PIN_PORT_C;
            break;
        case PORT_D:
            max_pin = MAX_PIN_PORT_D;
            break;
        case PORT_E:
            max_pin = MAX_PIN_PORT_E;
            break;
        default:
			/* Should not be here */
			break;
    }

    for(pin = 0; pin < max_pin; pin++)
    {
        switch(port)
        {
            case PORT_A:
                REG_SET_BIT(TRISA, pin, dir);
                break;
            case PORT_B:
                REG_SET_BIT(TRISB, pin, dir);
                break;
            case PORT_C:
                REG_SET_BIT(TRISC, pin, dir);
                break;
            case PORT_D:
                REG_SET_BIT(TRISD, pin, dir);
                break;
            case PORT_E:
                REG_SET_BIT(TRISE, pin, dir);
                break;
            default:
                /* Should not be here */
                break;
        }
    }
}

void GPIO_Update(void)
{
    /* Should do nothing */
}

void GPIO_Set_Port_Pin(tPort port, tPin pin, tPin_State port_state)
{
    switch(port)
    {
        case PORT_A:
            if(pin < MAX_PIN_PORT_A)
                REG_SET_BIT(PORTA, pin, port_state);
            break;
        case PORT_B:
            if(pin < MAX_PIN_PORT_B)
                REG_SET_BIT(PORTB, pin, port_state);
            break;
        case PORT_C:
            if(pin < MAX_PIN_PORT_C)
                REG_SET_BIT(PORTC, pin, port_state);
            break;
        case PORT_D:
            if(pin < MAX_PIN_PORT_D)
                REG_SET_BIT(PORTD, pin, port_state);
            break;
        case PORT_E:
            if(pin < MAX_PIN_PORT_E)
                REG_SET_BIT(PORTE, pin, port_state);
            break;
        default:
			/* Should not be here */
			break;
    }
}

void GPIO_Set_Port(tPort port, unsigned char state)
{
    unsigned char pin;
    unsigned char max_pin = 0;
    switch(port)
    {
        case PORT_A:
            max_pin = MAX_PIN_PORT_A;
            break;
        case PORT_B:
            max_pin = MAX_PIN_PORT_B;
            break;
        case PORT_C:
            max_pin = MAX_PIN_PORT_C;
            break;
        case PORT_D:
            max_pin = MAX_PIN_PORT_D;
            break;
        case PORT_E:
            max_pin = MAX_PIN_PORT_E;
            break;
        default:
			/* Should not be here */
			break;
    }

    for (pin = 0; pin < max_pin; pin++)
    {
        switch(port)
        {
            case PORT_A:
                if(pin < MAX_PIN_PORT_A)
                    REG_SET_BIT(PORTA, pin, (REG_GET_BIT(state, pin)));
                break;
            case PORT_B:
                if(pin < MAX_PIN_PORT_B)
                    REG_SET_BIT(PORTB, pin, (REG_GET_BIT(state, pin)));
                break;
            case PORT_C:
                if(pin < MAX_PIN_PORT_C)
                    REG_SET_BIT(PORTC, pin, (REG_GET_BIT(state, pin)));
                break;
            case PORT_D:
                if(pin < MAX_PIN_PORT_D)
                    REG_SET_BIT(PORTD, pin, (REG_GET_BIT(state, pin)));
                break;
            case PORT_E:
                if(pin < MAX_PIN_PORT_E)
                    REG_SET_BIT(PORTE, pin, (REG_GET_BIT(state, pin)));
                break;
            default:
                /* Should not be here */
                break;
        }
    }
}

tPin_State GPIO_Get_Port_Pin(tPort port, tPin pin)
{
    unsigned char ret = 0;

    switch(port)
    {
        case PORT_A:
            if(pin < MAX_PIN_PORT_A)
                ret = REG_GET_BIT(PORTA, pin);
            break;
        case PORT_B:
            if(pin < MAX_PIN_PORT_B)
                ret = REG_GET_BIT(PORTB, pin);
            break;
        case PORT_C:
            if(pin < MAX_PIN_PORT_C)
                ret = REG_GET_BIT(PORTC, pin);
            break;
        case PORT_D:
            if(pin < MAX_PIN_PORT_D)
                ret = REG_GET_BIT(PORTD, pin);
            break;
        case PORT_E:
            if(pin < MAX_PIN_PORT_E)
                ret = REG_GET_BIT(PORTE, pin);
            break;
        default:
			/* Should not be here */
			break;
    }

    return ret;
}


