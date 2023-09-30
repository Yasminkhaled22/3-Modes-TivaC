#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "Delay.h"
#include "Calculator.h"
#include "Timer_Mode.h"
#include "Stop_watch.h"
#include "Switch_Button.h"

extern int flag; 

int main (void)
{
  SYSCTL_RCGCGPIO_R |= 0x37;            //enable the clk to all the used ports
  Timer0A_Init(); 
  Timer1A_Init();
  LCD_init();                           // initialize the registers of the LCD in the main code
  keypad_Init();                        // initialize the registers of the keypad in the main code
  Buzzer_init();                        // initialize the registers of the buzzer in the main code
  Switch_Button_init();
  Timer_PB();
  Timer0_SetCallBack(Timer_mode);       // call back function has the address of the timer mode function
  Timer1_SetCallBack(stop_watch);       // call back function has the address of the stop watch function

  while(1)
  {
    if(flag==0)                            // first mode, calculator
    {
      while(flag==0)
      {
        calculator();
      }
    }

    else if(flag==1)                         //Second mode, Timer
    {
      Enter_Time();
      while(flag==1)
      {
        Timer_Counter();
      }
    }
    else if(flag==2)                          //Third mode, Stopwatch
    {
      while(flag==2)
      {
        if(((GPIO_PORTA_DATA_R &(1<<2))==0)) //START push button is pressed
        {
          Start_Stop_Watch();
        }
        else if((GPIO_PORTA_DATA_R &(1<<3))==0) //PAUSE  push button is pressed
        {
          Pause_Stop_Watch();
        }
        else if((GPIO_PORTA_DATA_R &(1<<5))==0) //RESET push button is pressed
        {
          Reset_Stop_Watch();
        }
      }
    }
  }
}
        
