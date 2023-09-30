#include "Timer_Mode.h"

char seconds1;   // the tenth second that is taken by the user 
char minutes1;   // the tenth minute that is taken by the user 
char seconds2;   // the unit second that is taken by the user 
char minutes2;  //  the unit minute that is taken by the user 
int seconds=0;   // the seconds in integar
uint32 minutes=0; // the minutes in integar
uint32 hours=0;
uint8 state=0;
char key;     // button that would be pressed to make the timer begin

void Enter_Time(void)
{
  LCD_Print("  00:00  ");
  delay_ms (1000);
  LCD_Clear();
  LCD_Print("ENTER mins & sec");
  delay_ms (1000);
  LCD_Clear();
  minutes1=keypad_getkey();
  LCD_Show (minutes1);
  delay_ms (30);
  minutes2=keypad_getkey();
  LCD_Show(minutes2);
  delay_ms (30);
  LCD_Show(':');
  delay_ms (30);
  seconds1=keypad_getkey();

  if(seconds1-48>5)
  {
          LCD_Print("ERROR");
          LCD_Clear();
          minutes1=keypad_getkey();
          LCD_Show (minutes1);
          minutes2=keypad_getkey();
          LCD_Show(minutes2);
          LCD_Show(':');
          seconds1=keypad_getkey();
  }
  else
  {
          LCD_Show(seconds1);  
  }

  seconds2=keypad_getkey();
  LCD_Show (seconds2);
  delay_ms (30);
  minutes=(((minutes1-48)*10)+(minutes2-48));
  seconds=(((seconds1-48)*10)+(seconds2-48));

  while (key != '/') 
  {
          key=keypad_getkey();
  }
  LCD_Clear();
  Timer0A_Enable(); 
}

void Timer_Counter(void)
{
  LCD_Cursor(0,0);
  if ( minutes<10)
  {
    LCD_Write_Integer(0);
    LCD_Write_Integer(minutes); 
  }
  else
  {
    LCD_Write_Integer(minutes); 
  }
  LCD_Cursor(0,2);
  LCD_Show(':');
  if ( seconds<10)
  {
    LCD_Write_Integer(0);
    LCD_Write_Integer(seconds); 
  }
  else
  {
    LCD_Write_Integer(seconds); 
  }
}
void Timer_mode(void)
{
  seconds--;
  if(minutes==0 && seconds==-1)
  {
     Timer0A_Deinit();
     Buzzer_on(); 
      delay_ms(500);
      Buzzer_off();
      seconds=0;
      minutes=0;
  }
  else if(minutes!= 0 && seconds==-1)
  {
          seconds=59;
          minutes--;
     
  }
}