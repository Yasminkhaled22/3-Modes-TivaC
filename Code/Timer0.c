#include "Timer0.h"
#include "tm4c123gh6pm.h"
#include "Buzzer.h"

static void (*g_Timer0_Call_Back_Ptr)(void) = NULL_PTR; // initialize the global pointer to point to NULL at first till it be called to point to address of function

void Timer0A_Init(void)
 { 
  TIMER0_CTL_R = 0;              //  disable TIMER0A during setup
  SYSCTL_RCGCTIMER_R |= 0x01;    // enable the clock 
  TIMER0_CFG_R = 0x4;            //  configure for 16-bit mode
  TIMER0_TAMR_R = 0x02;          //  configure for periodic mode, default down-count settings to count down from the reload value till it reaches zero
  TIMER0_TAILR_R = 64000;        //  reload value 64000
  TIMER0_TAPR_R = 255;           //  bus clock resolution to make a prescaler for 16 MHz by dividing it to 255 to get the time taken by the timer for one count
  TIMER0_ICR_R = 0x01;           //  clear TIMER0A timeout flag
  TIMER0_IMR_R |= 0x01;          //  arm timeout interrupt (Interrupt Mask Register)
  NVIC_EN0_R |= (1<<19);         // enable IRQ 19, NVIC_EN0_R is used to enable the interrupt sources whose IRQ numbers are 0-31 

}
void Timer0A_Deinit()            // disabling the timer
{
      TIMER0_CTL_R = 0;                      // disable TIMER0A throught the Control Register
}
void Timer0A_Handler(void)                   // the ISR function which contains the needed code to be happen when its condition occurs
{
   TIMER0_ICR_R = TIMER_ICR_TATOCINT;       // Used to clear the flag that make the ISR ouccrs in order not to be repeated once more untill the condition of it occurs
   if(g_Timer0_Call_Back_Ptr != NULL_PTR)   // checking that the global pointer to function is not equal to NULL (has an address to a certain function to be accessed)
  {
    (*g_Timer0_Call_Back_Ptr)();            // access the address of function which is stored in the pointer to make this function occurs
  } 
}
void Timer0_SetCallBack(void(*Ptr2Func)(void)) // set a function that make the global pointer to function contains the address of the needed instruction to occur
{
    g_Timer0_Call_Back_Ptr = Ptr2Func;         // global pointer to function contains the address of function needed to b estimated
}
