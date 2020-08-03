#include "E2PROM_Driver.h"

void E2PROM_init(void)
{
    i2c_init();
    
    e2pext_w(NUMBER_ADDR, INITIAL_NUMBER);
}

void E2PROM_update(void)
{
    /* DO NOTHING */
}

void E2PROM_set_number(unsigned char num)  // max stack depth 4
{
    e2pext_w(NUMBER_ADDR, num);
}

unsigned char E2PROM_get_number(void)  // max stack depth 3
{
    unsigned char ret = 0;
    
    ret = e2pext_r(NUMBER_ADDR);
    
    return ret;
}
