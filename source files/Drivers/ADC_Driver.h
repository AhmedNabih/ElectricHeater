#ifndef ADC_DRIVER_H_INCLUDED
#define ADC_DRIVER_H_INCLUDED

#include "ADC_Settings.h"

typedef enum
{
    ADC_CON0,  /* A: AN0-7      // D: -        // Vref+: VDD // Vref-: VSS */
    ADC_CON1,  /* A: AN0-2,4-7  // D: -        // Vref+: AN3 // Vref-: VSS */
    ADC_CON2,  /* A: AN0-4      // D: AN5-7    // Vref+: VDD // Vref-: VSS */
    ADC_CON3,  /* A: AN0-2, 4   // D: AN5-7    // Vref+: AN3 // Vref-: VSS */
    ADC_CON4,  /* A: AN0-1, 3   // D: AN2, 4-7 // Vref+: VDD // Vref-: VSS */
    ADC_CON5,  /* A: AN0-1      // D: AN2, 4-7 // Vref+: AN3 // Vref-: VSS */
    ADC_CON6,  /* A: -          // D: AN0-7    // Vref+: -   // Vref-: -   */
    ADC_CON7,  /* A: -          // D: AN0-7    // Vref+: -   // Vref-: -   */
    ADC_CON8,  /* A: AN0-1, 4-7 // D: -        // Vref+: AN3 // Vref-: AN2 */
    ADC_CON9,  /* A: AN0-5      // D: AN6-7    // Vref+: VDD // Vref-: VSS */
    ADC_CON10, /* A: AN0-2, 4-5 // D: AN6-7    // Vref+: AN3 // Vref-: VSS */
    ADC_CON11, /* A: AN0-1, 4-5 // D: AN6-7    // Vref+: AN3 // Vref-: AN2 */
    ADC_CON12, /* A: AN0-1, 4   // D: AN5-7    // Vref+: AN3 // Vref-: AN2 */
    ADC_CON13, /* A: AN0-1      // D: AN4-7    // Vref+: AN3 // Vref-: AN2 */
    ADC_CON14, /* A: AN0        // D: AN1-7    // Vref+: VDD // Vref-: VSS */
    ADC_CON15  /* A: AN0        // D: AN1, 4-7 // Vref+: AN3 // Vref-: AN2 */
} tADC_CONFIGRATION;

typedef enum
{
    ADC_ON = 1,
    ADC_OFF = 0
} tADC_STATE;

typedef enum
{
    ADC_CH0, // PORT_A PIN 0
    ADC_CH1, // PORT_A PIN 1
    ADC_CH2, // PORT_A PIN 2
    ADC_CH3, // PORT_A PIN 3
    ADC_CH4, // PORT_A PIN 5
    ADC_CH5, // PORT_E PIN 0
    ADC_CH6, // PORT_E PIN 1
    ADC_CH7  // PORT_E PIN 2
} tADC_CHANNEL;

typedef enum
{
    ADC_CLK0,
    ADC_CLK1,
    ADC_CLK2,
    ADC_CLK3,
    ADC_CLK4,
    ADC_CLK5,
    ADC_CLK6,
    ADC_CLK7
} tADC_CLOCK;

typedef enum
{
    ADC_ADJR = 1,
    ADC_ADJL = 0
} tADC_ADJUSMENT;

void ADC_init(tADC_CLOCK clk, tADC_CONFIGRATION config);
void ADC_update(void);
unsigned int ADC_get_result(tADC_ADJUSMENT adj, tADC_CHANNEL channel);

#endif // ADC_DRIVER_H_INCLUDED
