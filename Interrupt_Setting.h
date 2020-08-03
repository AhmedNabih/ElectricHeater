#ifndef INTERRUPT_SETTING_H_INCLUDED
#define INTERRUPT_SETTING_H_INCLUDED

#include <xc.h>

/* GLOBALS SETTINGS ENABLE */
#define GLOBAL_INTERRUPT_ENABLE(X) GIE = X // 1 = enable, 0 = disable
#define PERIPHERAL_INTERRUPT_ENABLE(X) PEIE = X // 1 = enable, 0 = disable

/* INNER SETTINGS ENABLE */
#define PORTB0_INTERRUPT_ENABLE(X) INTE = X // 1 = enable, 0 = disable
#define PORTB_INTERRUPT_ENABLE(X)  RBIE = X
/* INNER SETTINGS FLAGS */

// PortB pin0 Interrupt
// Notes: Flag must be cleared in software after each interrupt
// and cleared at first. => set to 0 to clear
#define PORTB0_SET_INTERRUPT_FLAG(X) INTF = X
#define PORTB0_GET_INTERRUPT_FLAG()  INTF
#define PORTB0_SET_EDGE(X)           INTEDG = X 
#define PORTB_SET_INTERRUPT_FLAG(X)  RBIF = X
#define PORTB_GET_INTERRUPT_FLAG()   RBIF


#endif // INTERRUPT_SETTING_H_INCLUDED
