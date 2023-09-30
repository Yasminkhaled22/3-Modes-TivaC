/*
 * LCD.c
 *  Author:
 *      Ahmet Eren ODACI
 *
 *  Credit:
 *      Lokman GÖKDERE
 *      http://www.mcu-turkey.com/stellaris-launchpad-16x2-lcd/
 */

#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"

#include "hw_memmap.h"
#include "sysctl.h"
#include "gpio.h"
#include "string.h"
//#include "Delay.h"

   
void SysCtlDelay(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3180;j++)
 {}
}   
   
void LCD_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

     //   SysCtlDelay(1000);

        GPIOPinWrite(LCDPORT, RS,  0x00 );

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
       SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

    //    SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

   //     SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

  //      SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

   //     SysCtlDelay(50000);


        LCD_Command(0x0F);    //Turn on Lcd
        LCD_Clear();          //Clear screen

}

void LCD_Command(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(1);

        GPIOPinWrite(LCDPORT, E, 0x00);

       SysCtlDelay(1);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(5);

        GPIOPinWrite(LCDPORT, E, 0x00);

       SysCtlDelay(1);

}

void LCD_Show(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(5);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(1);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(5);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(1);

}

void LCD_Cursor(char x, char y){

    if (x==0) {
        LCD_Command(0x80 + (y % 16));
        return;
    }
    LCD_Command(0xC0 + (y % 16));

}

void LCD_Clear(void){

        LCD_Command(0x01);
        SysCtlDelay(10);

}


void LCD_Yaz(char* s){

    int j, p=1, i;
    for (j=0; j<strlen(s)||j<15; j++) {
        LCD_Cursor(0, 15-j);
        for (i=0; i<strlen(s); i++) {
            LCD_Show(s[i]);
        }

        SysCtlDelay(8000000/3);
    }


    if (strlen(s)>16) {
        while (p < strlen(s)-16) {
            LCD_Cursor(0,0);
            for (j=0; j<16; j++) {
                LCD_Show(s[p+j]);
            }
            SysCtlDelay(800000/3);
            p++;
        }
        i = p;
        while (p < strlen(s) + i) {
            LCD_Cursor(0,0);
            for (j=0; j<16; j++) {
                LCD_Show(s[(p + j) % strlen(s)]);
            }
            SysCtlDelay(800000/3);
            p++;
        }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}


void LCD_PrintJustify(char i, char *s, char *d) {
    if (i==0) {
        for (i=0; i<strlen(s); i++) {
            LCD_Cursor(0, i);
            LCD_Show(s[i]);
        }
        for (i=0; i<strlen(d); i++) {
            LCD_Cursor(0, 15-i);
            LCD_Show(d[strlen(d)-i-1]);
        }
        LCD_Command(0xC0 + 16);
        return;
    }
    for (i=0; i<strlen(s); i++) {
        LCD_Cursor(1, i);
        LCD_Show(s[i]);
    }
    for (i=0; i<strlen(d); i++) {
        LCD_Cursor(1, 15-i);
        LCD_Show(d[strlen(d)-i-1]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

void LCD_Print(char *s) {
    int j;
    for (j=0; j<16; j++) {
        if (j<strlen(s)) {
            LCD_Cursor(0,j);
            LCD_Show(s[j]);
        }
    }
    SysCtlDelay(1000);
    LCD_Command(0xC0 + 16); //Hide cursor
}

void LCD_Write_Integer(int data)
{
  int num_to_be_displayed = 0;
  int i = 0, Multiplier = 1;
  if (data == 0)
  {
    LCD_Show(48);
  }
  while(data != 0)
  {
  num_to_be_displayed = (num_to_be_displayed * 10) + (data % 10);
  if (num_to_be_displayed == 0)
  {
    Multiplier *= 10;
  }
  data /= 10;
  }
  while (num_to_be_displayed != i)
	{
	 LCD_Show((num_to_be_displayed % 10) + 48);
	 num_to_be_displayed /= 10;
		if (!num_to_be_displayed)
		{
			num_to_be_displayed = Multiplier;
			i = 1;
		}
	}
}

void LCD_PrintLn(char i, char *s) {
    LCD_Cursor(i, 0);
    for (i=0; i<strlen(s); i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

void LCD_errormsg(void)
{
  LCD_Print("Math ERROR");
}
void displayTime(int h,int m,int s)
{
  //LCD_command(CLEAR_DISPLAY);
  for (int i=0; i<10 ;i++)
  {
    LCD_Cursor(0,0);
    LCD_Write_Integer(h);
    LCD_Cursor(0, 3);
    LCD_Show(':');
    LCD_Cursor(0, 4);
    LCD_Write_Integer(m);
    LCD_Cursor(0, 7);
    LCD_Show(':');
    LCD_Cursor(0, 8);
    LCD_Write_Integer(s);
  }
  LCD_Clear();
}
