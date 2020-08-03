#ifndef ADC_SETTINGS_H
#define	ADC_SETTINGS_H

#include <xc.h>

/********************************************************************************************
    A/D
        - Flag: ADON, Enable adc: 1, disable: 0
        - Flag: CHS2-0 , select where to get input, A0,A1,A2,A3,A5,E0,E1,E2
        - Flag: GO, set to 1 to start conversion, after conversion hardware set it to 0
        - Flag: PCFG3-0, select configuration for pins
        - Flag: ADFM, Result Format Select bit, 1 = right justified, 0 = left
********************************************************************************************/

#define ADC_SET_STATE(X)            ADON = X
#define ADC_SELECT_CHANNEL(X)       CHS2 = (X&0x4) >> 2;\
                                    CHS1 = (X&0x2) >> 1;\
                                    CHS0 = (X&0x1)
#define ADC_START_CONVERSION()      GO = 1
#define ADC_WAIT_CONVERSION()       while(GO == 1)
#define ADC_SET_CONFIGURATION(X)    PCFG3 = (X&0x8) >> 3;\
                                    PCFG2 = (X&0x4) >> 2;\
                                    PCFG1 = (X&0x2) >> 1;\
                                    PCFG0 = (X&0x1)
#define ADC_SELECT_RES_ADJUSMENT(X) ADFM = X
#define ADC_READ_RESULT(ADJ)        (ADJ)?(((unsigned int)((unsigned int)ADRESH)<<8)|(ADRESL)):((((unsigned int)ADRESH)<<2)|(ADRESL>>6))
#define ADC_SELECT_CLK(X)           ADCS2 = (X&0x4) >> 2;\
                                    ADCS1 = (X&0x2) >> 1;\
                                    ADCS0 = (X&0x1)


#endif	/* ADC_SETTINGS_H */

