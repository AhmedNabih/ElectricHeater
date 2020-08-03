#ifndef E2PROM_DRIVER_H
#define	E2PROM_DRIVER_H

#include "i2c.h"
#include "eeprom_ext.h"

#define INITIAL_NUMBER 60
#define NUMBER_ADDR    5

void E2PROM_init(void);
void E2PROM_update(void);
void E2PROM_set_number(unsigned char num); // max stack depth 4
unsigned char E2PROM_get_number(void); // max stack depth 3


#endif	/* E2PROM_DRIVER_H */

