#include "Calculator.h"

char key_1;
int x;
uint8 num_1[9];    //array to store the first number of the operand
uint8 num_2[9];    //array to store the second number of the operand

uint32 arr2[] ={1,10,100,1000,10000,100000,1000000};

uint32 i=0;      //index for the arrays
int num1=0;
int num2=0;
int c1=0;
int c2=0;
char operation;
int result=0;


void calculator(void)
{
  delay_ms(1000);
  LCD_Print("Enter num1:");
  delay_ms(1000);
  LCD_Clear();
  do{                          //to be sure that the user really entered a key.
          key_1= keypad_getkey();
          delay_ms(500);   //wait for the debounce
          if (key_1 >= '0' && key_1 <='9')
          {
                  LCD_Show(key_1);
                  num_1[i]=(key_1-48);
                  i++;
                  c1++;
          }
          if ((key_1=='$' && i==0))

          { 
                  //LCD_errormsg();
                  delay_ms(500);
                  LCD_Clear();
                  LCD_Print("Plz enter no :");
                  delay_ms(500);
                  LCD_Clear ();  
          }
         

  }while((key_1!='$')&& (i>0));

  num1 = storing (num_1 ,i);
  i=0;
  LCD_Print("Enter oper:");
  delay_ms(1500);
  LCD_Clear();

  do
  {
          delay_ms(200); 
          key_1= keypad_getkey();
          if (key_1 == '+')
          {
                  LCD_Show('+');
                  delay_ms(1000);
                  LCD_Clear();
                  operation = '+';
                  delay_ms(150);
                  break; 
          }

          else if (key_1 == '-')
          {
                  LCD_Show('-');
                  delay_ms(1500);
                  LCD_Clear();
                  operation = '-';
                  delay_ms(150);
                  break;
          }

          else if (key_1 == '*')
          {
                  LCD_Show('*');
                  delay_ms(1500);
                  LCD_Clear();
                  operation = '*';
                  delay_ms(150);
                  break;  
          }

          else if (key_1 == '/')
          {
                  LCD_Show('/');
                  delay_ms(1500);
                  LCD_Clear();
                  operation = '/';
                  delay_ms(150);
                  break;
          }

          else 
          {
                  LCD_Print("plz enter oper!");
                  delay_ms(150);
                  LCD_Clear();
          }
          LCD_Show(key_1);
          delay_ms(500);
  } while (key_1 != '+'||key_1 != '-'||key_1!= '*'||key_1 != '/');

  LCD_Print("Enter num2:");
  delay_ms(150);
  LCD_Clear();    
  do{                          //to be sure that the user really entered a key.
          key_1= keypad_getkey();
          delay_ms(200);   //wait for the debounce
          if (key_1 >= '0' && key_1 <='9' )
          {
                  LCD_Show(key_1);
                  num_2[x]=(key_1-48);
                  x++;
                  c2++;
          }
          if ((key_1=='$' && x==0))
          {
                  LCD_errormsg();
                  delay_ms(50);
                  LCD_Clear();
                  LCD_Print("Plz enter no :");
                  delay_ms(1500);
                  LCD_Clear();
          }

  }while((key_1!='$'&& x>0));

  num2 = storing (num_2 , x);
  LCD_Clear();
  LCD_Cursor(0, 1);
  LCD_Write_Integer(num1);
  LCD_Cursor(0, (c1+1));
  LCD_Show(operation);
  LCD_Cursor(0, (c1+3));
  LCD_Write_Integer(num2);
  delay_ms(1500);

  key_1 = keypad_getkey();
  delay_ms(200);   //wait for the debounce

  if (key_1 == '=')
  {
          LCD_Cursor(1, 0);
          LCD_Show(key_1);
          delay_ms(1000);
          switch (operation)
          {
          case '+':
          {
                  result = addition( num1,num2);
                  break;
          }
          case '-':
          {
                  result = subtraction( num1,num2);
                  break;
          }
          case '*':
          {
                  result = multiplication( num1,num2);
                  break;
          }
          case '/':
          {
                  result = divide ( num1 ,num2);
                  break;
          }
          }
          LCD_Cursor(1, 1);
          LCD_Write_Integer(result);
          delay_ms(2000);
          LCD_Clear();
          clear_data();
          delay_ms(5000);
  }
}

int addition (int num1, int num2)
{
	result = num1 + num2;
	return result;
}

int subtraction (int num1, int num2)
{ 
	result = num1 - num2;
	return result;
}

int multiplication (int num1, int num2)
{
	result = num1 * num2;
	return result;
}

float divide (int num1, int num2)
{
	if(num2 == 0)
	{
		LCD_Print("error");
	}

	else if(num1 == 0)
	{
		result =0;
	}

	else
	{
		result = (num1 / num2);
	}
	return result;
}

void clear_data()
{
	num1 = 0;
	num2 = 0;
	result = 0;
	c1=0;
	key_1 = 0;
	operation=0;
	i=0;
	for (int z=0; z<9; z++)
	{
		num_1[z]=0;
	}
	for (int z=0; z<9; z++)
	{
		num_2[z]=0;
	}

}

int storing(uint8 arr[],uint32 x)
{ 
	int no =0;
	for (int y=0; y<x;y++)
	{
		no += (arr[y] * arr2[x-y-1]);
	} 
	return no;
}