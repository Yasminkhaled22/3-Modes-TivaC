#ifndef Timer0_H_
#define Timer0_H_
#define NULL_PTR ((void*)0)

void Timer0A_Init(void);    // initializing the timer0A
void Timer0A_Handler(void); // the ISR function which contains the needed code to be happen when its condition occurs
void Timer0A_Deinit();  // disabling the timer
void Timer0_SetCallBack(void(*Ptr2Func)(void)); // set a function that make the global pointer to function contains the address of the needed instruction to occur

#endif