#include "ADC_Driver.h"


void ADC_init(tADC_CLOCK clk, tADC_CONFIGRATION config)
{
    ADC_SET_STATE(ADC_OFF);
    ADC_SELECT_CLK(clk);
    ADC_SET_CONFIGURATION(config);
}

void ADC_update(void)
{

}

unsigned int ADC_get_result(tADC_ADJUSMENT adj, tADC_CHANNEL channel)
{
    unsigned int ret = 0;

    ADC_SELECT_RES_ADJUSMENT(adj);
    ADC_SELECT_CHANNEL(channel);
    ADC_SET_STATE(ADC_ON);
    ADC_START_CONVERSION();
    ADC_WAIT_CONVERSION();
    ret = ADC_READ_RESULT(adj);
    ADC_SET_STATE(ADC_OFF);

    return ret;
}
