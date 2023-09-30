
#include "Timer1.h"
#include "tm4c123gh6pm.h"

static void (*g_Timer1_Call_Back_Ptr)(void) = NULL_PTR;

void Timer1A_Init(void)
{
  
  SYSCTL_RCGCTIMER_R |= (1<<1);    //  enable the clock 
  TIMER1_CTL_R = 0;                //  disable TIMER1A during setup
  TIMER1_CFG_R = 0x04;             //  configure for 16-bit mode
  TIMER1_TAMR_R = 0x02;            //  configure for periodic mode, default down-count settings to count down from the reload value till it reaches zero
  TIMER1_TAPR_R = 255;             //  bus clock resolution to make a prescaler for 16 MHz by dividing it to 255 to get the time taken by the timer for one count
  TIMER1_IMR_R |= (1<<0);          //  arm timeout interrupt (Interrupt Mask Register)
  TIMER1_TAILR_R = 64000;          //  reload value 64000
  TIMER1_ICR_R = 0X01;             //  clear TIMER0A timeout flag
  NVIC_EN0_R = (1<<21);            // enable IRQ 21, NVIC_EN0_R is used to enable the interrupt sources whose IRQ numbers are 0-31 
  TIMER1_CTL_R = 0;
  
}

void Timer1A_Handler(void)                // the ISR function which contains the needed code to be happen when its condition occurs
{
   TIMER1_ICR_R = TIMER_ICR_TATOCINT;     // Used to clear the flag that make the ISR ouccrs in order not to be repeated once more untill the condition of it occurs
   if(g_Timer1_Call_Back_Ptr != NULL_PTR) // checking that the global pointer to function is not equal to NULL (has an address to a certain function to be accessed)
  {
    (*g_Timer1_Call_Back_Ptr)();          // access the address of function which is stored in the pointer to make this function occurs
  } 
      
}

void Timer1_SetCallBack(void(*Ptr2Func)(void)) // set a function that make the global pointer to function contains the address of the needed instruction to occur
{
    g_Timer1_Call_Back_Ptr = Ptr2Func; // global pointer to function contains the address of function needed to b estimated
}


