#ifndef ELECTRIC_HEATER_SYSTEM_H
#define	ELECTRIC_HEATER_SYSTEM_H

/* ############################################# */
/* ################### Init #################### */
/* ############################################# */
void System_Init(void);
void System_Start(void);
void System_UserInteraction_Check(void);
void System_Heater_Mood(void);
void System_Heater_Update(void);
void System_Cooler_Mood(void);
void System_Cooler_Update(void);
void System_Temp_Update(void);
void System_Select_Mood(void);
void System_Write_Data(void);
void System_Read_Data(void);
/* ############################################# */
/* ################## Display ################## */
/* ############################################# */

// ############## Check Functions ############## //
// every 320
// max stack depth 2
void System_Display_Check(void);

// every 24 ms
// max stack depth 4
void System_Display_Check_Setting_Mood(void); // priority high cuz time counting

// every 352 ms
// max stack depth 2
void System_Display_Check_Heater_Mood(void);

// every 360 ms
// max stack depth 2
void System_Display_Check_Cooler_Mood(void);

// ############## Mood Functions ############## //
// every 1000 ms
// max stack depth 2
void System_Display_Setting_Mood(void);

// every 1000 ms
// max stack depth 2
void System_Display_Heater_Mood(void);

// every 1000 ms
// max stack depth 2
void System_Display_Cooler_Mood(void);

// ######## Hardware update Functions ######### //

// every 8 ms
// max stack depth 2
void System_Display_Update(void);

#endif	/* ELECTRIC_HEATER_SYSTEM_H */

