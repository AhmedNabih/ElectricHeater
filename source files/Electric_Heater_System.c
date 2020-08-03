#include "Electric_Heater_System.h"

#include "ADC_Driver.h"
#include "COOLER_Driver.h"
#include "HEATER_Driver.h"
#include "SSD_Driver.h"
#include "PB_Driver.h"
#include "LED_Driver.h"
#include "E2PROM_Driver.h"
#include "Interrupt_Setting.h"
#include "TIMER0_Driver.h"
#include "TEMP_Driver.h"
#include "main.h"

static boolean temp_mood = FALSE;
static boolean setting_mood = FALSE;
static boolean heater_mood = FALSE;
static boolean cooler_mood = FALSE;
static boolean button_signal = FALSE;
static boolean read_data = FALSE;
static unsigned char sensed_temp = 0;
static unsigned char e2prom_temp = 0;
static unsigned char displayed_temp = 0;

void System_Init(void)
{
    /* E2PROM initialization */
    E2PROM_init();
    e2prom_temp = E2PROM_get_number();
    
    /* ADC initialization */
    ADC_init(ADC_CLK1, ADC_CON0);
    
    /* Temperature sensor initialization */
    TEMP_init();
    //sensed_temp = TEMP_get_temp();
    
    /* Heater and Cooler initialization */
    HEATER_init(HEATER_OFF);
    COOLER_init(COOLER_OFF);
    
    /* Timer0 initialization */
    TIMER0_init(T0_PRE_256, T0_INTERNAL_CLK);
    
    /* seven segment display initialization */
    SSD_init(SSD_MR, SSD_OFF, SSD_0);
    SSD_init(SSD_R, SSD_OFF, SSD_0);
    displayed_temp = sensed_temp;
    
    /* Push Button initialization */
    PB_init(PB_UP_TEMP, PB_RELEASED);
    PB_init(PB_DOWN_TEMP, PB_RELEASED);
    PB_init(PB_ON_OFF_HEATER, PB_RELEASED);
    
    /* LED initialization */
    LED_init(LED_HEATER, LED_OFF);
    LED_init(LED_COOLER, LED_OFF);
}

void System_Start(void)
{
    GLOBAL_INTERRUPT_ENABLE(1);
    TIMER0_start(1);
}

void System_Display_Check(void)
{
    if( (heater_mood == FALSE) && 
        (cooler_mood == FALSE) )
    {
        SSD_set_state(SSD_MR, SSD_OFF);
        SSD_set_state(SSD_R, SSD_OFF);
        
        LED_off(LED_HEATER);
        LED_off(LED_COOLER);
    }
}

#define MAX_SET_TEMP 75
#define MIN_SET_TEMP 35

void System_UserInteraction_Check(void)
{
    PB_update();
    
    if( (setting_mood == TRUE) &&
        (PB_get_state(PB_UP_TEMP) == PB_PRE_RELEASED) )
    {
        e2prom_temp++;
        
    }
    
    if( (setting_mood == TRUE) &&
        (PB_get_state(PB_DOWN_TEMP) == PB_PRE_RELEASED) )
    {
        e2prom_temp--;
    }
    
    if(e2prom_temp > MAX_SET_TEMP)
        e2prom_temp = MAX_SET_TEMP;
    if(e2prom_temp < MIN_SET_TEMP)
        e2prom_temp = MIN_SET_TEMP;
    
    if( (PB_get_state(PB_UP_TEMP) == PB_PRE_RELEASED) ||
        (PB_get_state(PB_DOWN_TEMP) == PB_PRE_RELEASED) )
    {
        if(setting_mood == FALSE)
        {
            setting_mood = TRUE;
        }
        else
        {
            button_signal = TRUE;
        }
        
    }
    
    if( (PB_get_state(PB_ON_OFF_HEATER) == PB_PRE_RELEASED) )
    {
        if(temp_mood == TRUE)
        {
            temp_mood = FALSE;
        }
        else if(temp_mood == FALSE)
        {
            temp_mood = TRUE;
        }
    }

}

void System_Write_Data(void) // time bounded
{
    E2PROM_set_number(e2prom_temp);
}

void System_Read_Data(void) // event bounded
{
    if(read_data == TRUE)
    {
        e2prom_temp = E2PROM_get_number();
        read_data = FALSE;
    }
}

#define SETTING_MOOD_MAX_TIME 26

void System_Display_Check_Setting_Mood(void)
{
    static unsigned char setting_mood_timer = 0;
    
    if( (setting_mood == TRUE) )
    {
        displayed_temp = e2prom_temp;
    }
    else
    {
        displayed_temp = sensed_temp;
    }
    
    if( (setting_mood == TRUE) && 
        (setting_mood_timer < SETTING_MOOD_MAX_TIME) && 
        (button_signal == TRUE) )
    {
        setting_mood_timer = 0;
        button_signal = FALSE;
    }
    
    if((setting_mood == TRUE) &&
        setting_mood_timer >= SETTING_MOOD_MAX_TIME)
    {
        setting_mood = FALSE;
        setting_mood_timer = 0;
        button_signal = FALSE;
    }
    
    setting_mood_timer++;
}

void System_Display_Setting_Mood(void)
{
    if(setting_mood == TRUE)
    {
        SSD_toggle_all();
    }
}

void System_Display_Check_Heater_Mood(void)
{
    if(heater_mood == TRUE)
    {
        SSD_set_state(SSD_MR, SSD_ON);
        SSD_set_state(SSD_R, SSD_ON);
        
        LED_on(LED_HEATER);
    }
    else
    {
        LED_off(LED_HEATER);
    }
}

void System_Display_Heater_Mood(void)
{
    if(heater_mood == TRUE)
    {
        LED_toggle(LED_HEATER);
    }
}

void System_Display_Check_Cooler_Mood(void)
{
    if(cooler_mood == TRUE)
    {
        SSD_set_state(SSD_MR, SSD_ON);
        SSD_set_state(SSD_R, SSD_ON);
    }
    else
    {
        
    }
}

void System_Display_Cooler_Mood(void)
{
    if(cooler_mood == TRUE)
    {
        LED_on(LED_COOLER);
    }
    else
    {
        LED_off(LED_COOLER);
    }
}

void System_Display_Update(void)
{
    /* SSD hardware update */
    SSD_set_number(displayed_temp);
    SSD_update();
    
    /* LED hardware update */
    LED_update();
}

void System_Heater_Mood(void)
{
    if(heater_mood == TRUE)
    {
        HEATER_set_state(HEATER_ON);
    }
    else
    {
        HEATER_set_state(HEATER_OFF);
    }
}

void System_Heater_Update(void)
{
    HEATER_update();
}

void System_Cooler_Mood(void)
{
    if(cooler_mood == TRUE)
    {
        COOLER_set_state(COOLER_ON);
    }
    else
    {
        COOLER_set_state(COOLER_OFF);
    }
}

void System_Cooler_Update(void)
{
    COOLER_update();
}

void System_Temp_Update(void)
{
    TEMP_update();
    sensed_temp = TEMP_get_temp();
}

#define TEMP_MARGIN 4
void System_Select_Mood(void)
{
    static boolean first_time = FALSE;
    static boolean lock_cooler_mood = FALSE;
    static boolean lock_heater_mood = FALSE;
    unsigned char avg_temp;
    
    if(temp_mood == TRUE)
    {
        avg_temp = TEMP_avg_get_temp();
        
        if(lock_cooler_mood == FALSE)
        {
            if( (avg_temp + TEMP_MARGIN < e2prom_temp) && (lock_heater_mood == FALSE) )
                lock_heater_mood = TRUE;
            if( (avg_temp > e2prom_temp + TEMP_MARGIN) && (lock_heater_mood == TRUE) )
                lock_heater_mood = FALSE;
        }

        if(lock_heater_mood == FALSE)
        {
            if( (avg_temp > e2prom_temp + TEMP_MARGIN) && (lock_cooler_mood == FALSE) )
                lock_cooler_mood = TRUE;
            if( (avg_temp + TEMP_MARGIN < e2prom_temp) && (lock_cooler_mood == TRUE) )
                lock_cooler_mood = FALSE;
        }

        if(lock_cooler_mood == TRUE)
        {
            cooler_mood = TRUE;
        }
        else if(lock_cooler_mood == FALSE)
        {
            cooler_mood = FALSE;
        }

        if(lock_heater_mood == TRUE)
        {
            heater_mood = TRUE;
            if(read_data == FALSE && first_time == FALSE)
            {
                read_data = TRUE;
                first_time = TRUE;
            }
        }
        else if(lock_heater_mood == FALSE)
        {
            heater_mood = FALSE;
            read_data = FALSE;
            first_time = FALSE;
        }
    }
    else
    {
        first_time = FALSE;
        lock_cooler_mood = FALSE;
        lock_heater_mood = FALSE;
    }
    

}