#include "LED_Driver.h"

typedef struct
{
    tLED led;
    tPort port;
    tPin pin;
    tLED_state state;
    unsigned char is_init;
} tLED_info;

static tLED_info led_info[LED_NUMBER] =
{
    {LED_HEATER, LED_PORT, PIN_6, LED_OFF, 0},
    {LED_COOLER, LED_PORT, PIN_7, LED_OFF, 0}
};

void LED_init(tLED led, tLED_state initial_state)
{
    GPIO_Port_Pin_Init(led_info[led].port, led_info[led].pin, GPIO_OUT);
    led_info[led].is_init = 1;
    led_info[led].state = initial_state;
}

void LED_update(void)
{
    unsigned char led;
    for(led = 0; led < LED_NUMBER; led++)
    {
        if(led_info[led].is_init == 1)
        {
            GPIO_Set_Port_Pin(led_info[led].port, led_info[led].pin, led_info[led].state);
        }
    }
}

void LED_on(tLED led)
{
    led_info[led].state = LED_ON;
}

void LED_off(tLED led)
{
    led_info[led].state = LED_OFF;
}

tLED_state LED_get_state(tLED led)
{
    unsigned char ret = 0;

    ret = led_info[led].state;

    return ret;
}

void LED_toggle(tLED led)
{
    if(led_info[led].state == LED_ON)
        led_info[led].state = LED_OFF;
    else
        led_info[led].state = LED_ON;
}
