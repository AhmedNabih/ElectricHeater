#include "TEMP_Driver.h"

void TEMP_init(void)
{
    temp = 0;
    avg_temp = 0;
    unsigned char i = 0;
    for(; i < AVG_CYCLE; i++)
        avg_temp_cycle[i] = 0;
    
    // temp. sensor port pin
    GPIO_Port_Pin_Init(PORT_A, PIN_2, GPIO_IN);
}

void TEMP_update(void)
{
    static unsigned char cycle = 0;
    unsigned char i;
    unsigned int readTemp, avgTemp;
    
    if(cycle >= 10)
    {
        avgTemp = 0;
        for(i = 0; i < AVG_CYCLE; i++)
            avgTemp += avg_temp_cycle[i];
        avgTemp /= AVG_CYCLE;
        
        avg_temp = avgTemp;
        
        cycle = 0;
    }
    
    readTemp = ADC_get_result(ADC_ADJR, TEMP_CH);
    temp = ((readTemp * 100) / 204);
    avg_temp_cycle[cycle] = temp;
    
    cycle++;
}

unsigned char TEMP_get_temp(void)
{
    return temp;
}

unsigned char TEMP_avg_get_temp(void)
{
    return avg_temp;
}
