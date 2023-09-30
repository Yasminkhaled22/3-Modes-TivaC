
#include "Timer1.h"
#include "tm4c123gh6pm.h"

static void (*g_Timer1_Call_Back_Ptr)(void) = NULL_PTR;

void Timer1A_Init(void)
{
  
  SYSCTL_RCGCTIMER_R |= (1<<1);
  TIMER1_CTL_R = 0;
  TIMER1_CFG_R = 0x04;
  TIMER1_TAMR_R = 0x02;
  TIMER1_TAPR_R = 255;
  TIMER1_IMR_R |= (1<<0);
  TIMER1_TAILR_R = 64000;
  TIMER1_ICR_R = 0X01;
  NVIC_EN0_R = (1<<21);
  TIMER1_CTL_R = 0; 
}

void Timer1A_Deinit(void)
{
      TIMER1_CTL_R = 0;
}

void Timer1A_Enable(void)
{
  TIMER1_CTL_R |= 0x01; 
}
void Timer1A_Handler(void)
{
   TIMER1_ICR_R = TIMER_ICR_TATOCINT;
   if(g_Timer1_Call_Back_Ptr != NULL_PTR)
  {
    (*g_Timer1_Call_Back_Ptr)();
  }   
}

void Timer1_SetCallBack(void(*Ptr2Func)(void))
{
    g_Timer1_Call_Back_Ptr = Ptr2Func;
}


