#ifndef Timer1_H_
#define Timer1_H_

#include "types.h"

#define PB_Reset_Port_Id   PORTF_ID     //identify the port_ID for the reset push button
#define PB_Pause_Port_Id   PORTF_ID     //identify the port_ID for the Pause push button
#define PB_Resume_Port_Id  PORTF_ID     //identify the port_ID for the Resume push button

#define PB_Reset_Pin_Id    PIN1_ID      //identify the pin_ID for the reset push button
#define PB_Pause_Pin_Id    PIN0_ID      //identify the pin_ID for the pause push button
#define PB_Resume_Pin_Id   PIN4_ID      //identify the pin_ID for the resume push button
                     
void Timer1A_Init(void);                // initializing the timer0A
void Timer1A_Handler(void);             // the ISR function which contains the needed code to be happen when its condition occurs
void Timer1_SetCallBack(void(*Ptr2Func)(void)); // set a function that make the global pointer to function contains the address of the needed instruction to occur

#endif