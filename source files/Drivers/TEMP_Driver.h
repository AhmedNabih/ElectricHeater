#ifndef TEMP_DRIVER_H
#define	TEMP_DRIVER_H

#include "ADC_Driver.h"
#include "GPIO_Driver.h"

#define TEMP_PORT   PORT_A
#define TEMP_CH     ADC_CH2
#define AVG_CYCLE   10

static unsigned char temp;
static unsigned char avg_temp;
static unsigned char avg_temp_cycle[AVG_CYCLE];

void TEMP_init(void);
void TEMP_update(void);
unsigned char TEMP_get_temp(void);
unsigned char TEMP_avg_get_temp(void);

#endif	/* TEMP_DRIVER_H */

