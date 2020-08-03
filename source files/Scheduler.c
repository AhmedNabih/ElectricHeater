#include "Scheduler.h"
#include "Electric_Heater_System.h"
#include "main.h"

void Scheduler_Update(void)
{
    static unsigned int counter = 0;
    if(flag == TRUE)
    {
        counter += TICK_MS;
        flag = FALSE;
    }
    
    if(counter % 58 == 0)
    {
        System_UserInteraction_Check();
        System_Select_Mood();
    }
    
    if(counter % 4 == 0)
    {
        System_Display_Update();
    }
    
    if(counter % 108 == 0)
    {
        System_Display_Check();
        System_Display_Check_Heater_Mood();
        System_Display_Check_Cooler_Mood();
    }
    
    if(counter % 216 == 0)
    {
        System_Display_Check_Setting_Mood();
    }
    
    if(counter % 100 == 0)
    {
        System_Temp_Update();
    }
    
    if(counter == 1000)
    {
        System_Display_Setting_Mood();
        System_Display_Heater_Mood();
        System_Display_Cooler_Mood();
    } 
    
    if(counter % 316 == 0)
    {
        System_Heater_Mood();
        System_Cooler_Mood();
    }
    
    if(counter % 220 == 0)
    {
        System_Heater_Update();
        System_Cooler_Update();
    }
    
    if(counter % 500 == 0)
    {
        System_Write_Data();
    }
    
    if(counter % 252 == 0)
    {
        System_Read_Data();
    }
    
    if(counter == 1000)
    {
        counter = 0;
    }
}
