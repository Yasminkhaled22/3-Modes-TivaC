#ifndef Timer1_H_
#define Timer1_H_

#include "types.h"

#define PB_Reset_Port_Id   PORTF_ID
#define PB_Pause_Port_Id   PORTF_ID
#define PB_Resume_Port_Id  PORTF_ID

#define PB_Reset_Pin_Id    PIN1_ID
#define PB_Pause_Pin_Id    PIN0_ID
#define PB_Resume_Pin_Id   PIN4_ID

void stop_watch();
void Timer1A_Init(void);
void Timer1A_Deinit(void);
void Timer1A_Enable(void);
void Timer1A_Handler(void);
void Timer1_SetCallBack(void(*Ptr2Func)(void));


#endif