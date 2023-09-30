#include "Stop_watch.h"

int seconds_;
int minutes_;


void Start_Stop_Watch(void)
{
  Timer1A_Enable();
  while((TIMER1_CTL_R == 0x01) && ((GPIO_PORTA_DATA_R&(1<<3))!=0) && ((GPIO_PORTA_DATA_R &(1<<5))!=0))
  {
    if (seconds_ < 10) 
    {
      LCD_Cursor(0,4); 
      LCD_Command(0x0c);

      //write zero
      LCD_Write_Integer(seconds_);
      LCD_Command(0x10);

    } 
    else if (seconds_ < 60) 
    {
      LCD_Cursor(0,3);
      LCD_Command(0x0c);
      LCD_Write_Integer(seconds_);

    } 
    else
    {
      LCD_Cursor(0,3);
      LCD_Command(0x0c);
      LCD_Write_Integer(0);
      seconds_ = 0;
      LCD_Cursor(0,4);
      LCD_Command(0x0c);

      LCD_Write_Integer(seconds_);
      minutes_++;
      if (minutes_ < 10) 
      {
        LCD_Cursor(0,0);
        LCD_Command(0x0c);

        LCD_Write_Integer(0);
        LCD_Cursor(0,1);
        LCD_Command(0x0c);

        LCD_Write_Integer(minutes_);
      } 
      else 
      {
        LCD_Cursor(0,0);
        LCD_Command(0x0c);
        LCD_Write_Integer(minutes_);
      }
    }
  }
}

void Pause_Stop_Watch(void)
{
  Timer1A_Deinit();
}
void Reset_Stop_Watch(void)
{
  seconds_ =0;
  minutes_=0;
  LCD_Cursor(0,0);
  LCD_Write_Integer(minutes_);
  LCD_Cursor(0,1);
  LCD_Write_Integer(minutes_);
  LCD_Cursor(0,3);
  LCD_Write_Integer(seconds_);
  LCD_Cursor(0,4);
  LCD_Write_Integer(seconds_);
  Timer1A_Deinit();
}

void stop_watch(void)
{
  seconds_ ++;
}

void Timer_PB(void)
{
  SYSCTL_RCGCGPIO_R |= 0x01;
  while((SYSCTL_PRGPIO_R& 0x01) == 0){};
  GPIO_PORTA_LOCK_R = 0x4C4F434B;
  GPIO_PORTA_CR_R = 0x2C;
  GPIO_PORTA_DIR_R &=~ (1<<2)|~(1<<5) |~(1<<3);
  GPIO_PORTA_PUR_R |= (1<<2)|(1<<5)|(1<<3);
  GPIO_PORTA_DEN_R|= (1<<2)|(1<<5)|(1<<3);   
}