#ifndef INTERRUPT_H_INCLUDED
#define INTERRUPT_H_INCLUDED

#include <xc.h>
#include "Interrupt_Setting.h"
#include "TIMER0_Driver.h"

void __interrupt() interrupty();

#endif // INTERRUPT_H_INCLUDED
