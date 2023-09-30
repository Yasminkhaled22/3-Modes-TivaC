#ifndef Timer0_H_
#define Timer0_H_

#include "types.h"

void Timer0A_Init(void);
void Timer0A_Handler(void);
void Timer0A_Deinit(void);
void Timer0A_Enable(void);
void Timer0_SetCallBack(void(*Ptr2Func)(void));

#endif