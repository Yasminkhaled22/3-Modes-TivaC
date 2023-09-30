#include <Timer0.h>
#include "tm4c123gh6pm.h"

static void (*g_Timer0_Call_Back_Ptr)(void) = NULL_PTR;

void Timer0A_Init(void)
 { 
  SYSCTL_RCGCTIMER_R |= 0x01;
  TIMER0_CTL_R = 0;    //  disable TIMER0A during setup
  TIMER0_CFG_R = 0x4;    //  configure for 16-bit mode
  TIMER0_TAMR_R = 0x02;   //  configure for periodic mode, default down-count settings
  TIMER0_TAPR_R |= 0xFF;            //  bus clock resolution
  TIMER0_IMR_R |= 0x01;    //  arm timeout interrupt
  TIMER0_TAILR_R = 64000-1;    //  reload value 32 64000
  TIMER0_ICR_R = 0x01;    //  clear TIMER0A timeout flag
  NVIC_EN0_R |= (1<<19);   
  TIMER0_CTL_R = 0;    //  disable TIMER0A during setup
}
void Timer0A_Deinit(void)
{
      TIMER0_CTL_R = 0;
}
void Timer0A_Enable(void)
{
  TIMER0_CTL_R = 0x01; 
}
void Timer0A_Handler(void)
{
   TIMER0_ICR_R = TIMER_ICR_TATOCINT;
   if(g_Timer0_Call_Back_Ptr != NULL_PTR)
  {
    (*g_Timer0_Call_Back_Ptr)();
  } 
}
void Timer0_SetCallBack(void(*Ptr2Func)(void))
{
    g_Timer0_Call_Back_Ptr = Ptr2Func;
}


