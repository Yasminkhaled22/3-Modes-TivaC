#include <stdbool.h>
#include <stdint.h>
#include <lcd.h>
#include "keypad.h"
#include "sysctl.h"
#include "Buzzer.h"
#include "Delay.h"
#include "Timer1.h"
#include "Timer0.h"

/*Calculator var*/
char key_1;        // variable to store in it what is taken from the user from keypad
uint8 num_1[9];    //array to store the first number of the operand
uint8 num_2[9];    //array to store the second number of the operand

uint32 arr2[] ={1,10,100,1000,10000,100000,1000000};  // array is used in converting the characters entered by the user into a whole number (used in the storing function)
uint32 x;        //index for the  second array
uint32 i=0;      //index for the first arrays
uint8 key;       //to recieve the returned character
int num1=0;      //the first number entered by the user will be stored in it
int num2=0;      //the second number entered by the user will be stored in it
int c1=0;        //variable is used to increment by 1 every time the user enter a character of the first digit
int c2=0;        //variable is used to increment by 1 every time the user enter a character of the second digit
char operation;  //store the type of operation needed by the user
int result=0;    //variable for storing the result in it

/*Timer var*/
char seconds1;   // the tenth second that is taken by the user 
char minutes1;   // the tenth minute that is taken by the user 
char seconds2;   // the unit second that is taken by the user 
char minutes2;  //  the unit minute that is taken by the user 
int seconds=0;   // the seconds in integar
uint32 minutes=0; // the minutes in integar
uint8 state=0;
char key__;     // button that would be pressed to make the timer begin

/*stop watch var*/
int seconds_;   //seconds to be incremented by the stop watch
int minutes_;   //minutes to be incremented by the stop watch

int flag=0; //interruot var
void init()
{
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R=0x04;
	GPIO_PORTD_PUR_R |= (1<<3);
	GPIO_PORTD_DIR_R &= ~(1<<3); 
	GPIO_PORTD_DEN_R|= (1<<3); 

	NVIC_EN0_R|= (1<<3); 
        GPIO_PORTD_IS_R  = 0x00;     // edge  
        GPIO_PORTD_IBE_R = 0x00; 
        GPIO_PORTD_IEV_R = 0x00;    //negative edge, used to determine the detecting edges or levels( 0: A falling edge or a LOW level, 1: A rising edge or a HIGH level )
	GPIO_PORTD_ICR_R = 0x1 ;    // Clear the raw interruot register
	GPIO_PORTD_IM_R  |= (1<<3);
}

void GPIOD_Handler(void)
{
  	GPIO_PORTD_ICR_R=0x1;

         flag++;         // increment the flag to move from mode to mode  

         if(flag>2)       // flag is used for 3 modes so it has to be with 3 different variables only (0,1,2)
        {
           flag=0;   // if it is incremented than 2 make it equal zero to go to the first mode (calculator)
        }       
}

int addition (int num1, int num2)  //addition function of the calculator 
{
	result = num1 + num2;
	return result;
}

int subtraction (int num1, int num2) //subtraction function of the calculator 
{ 
	result = num1 - num2;
	return result;
}

int multiplication (int num1, int num2) //multiplication function of the calculator 
{
	result = num1 * num2;
	return result;
}

float divide (int num1, int num2) //division function of the calculator 
{
	if(num2 == 0)  // if the second no equal zero then it will be num1/0 (undefined)
	{
	   LCD_Print("error"); //error message will appear
	}

	else if(num1 == 0)  // if the first no equal zero then it will be 0/num2 =0
	{
	   result =0;
	}

	else
	{
	   result = (num1 / num2);
	}
	return result;    // send the result of the operations 
}

void clear_data()   //function is used at the end of the calculator mode to clear all of its variables 
{
	num1 = 0;  // clear all the used variables
	num2 = 0;
	result = 0;
	c1=0;
	key = 0;
	operation=0;
	i=0;
	for (int z=0; z<9; z++)   // to clear the array of the first number
	{
		num_1[z]=0;       // make all the index in the first array equal to zero
	}
	for (int z=0; z<9; z++)   // to clear the array of the second number
	{
		num_2[z]=0;       // make all the index in the second array equal to zero
	}
        
}

int storing(uint8 arr[],uint32 x)
{ 
	int no =0;               // local variable tto store the whole digit in it
	for (int y=0; y<x;y++)
	{
		no += (arr[y] * arr2[x-y-1]); // storing the whole no 
	} 
	return no;
}
void Timer_mode(void)
{
	seconds--;                     // decrement the seconds 
        if(minutes==0 && seconds==-1)  // if the minutes equal zero and the seconds decrement than zero 
	{
		Buzzer_on();         //enable the buzzer
                delay_ms(1500);
		Timer0A_Deinit();     //disable the timer to stop decrementing in time 
		Buzzer_off();         // disable the buzzer
                seconds=0;            // make seconds equal zero
                minutes=0;            // make minutes equal zero
	}
	if(seconds==-1)              //if the seconds decrement than zero but the minutes are not equal zero
	{
		seconds=59;          // make seconds equal 59
		minutes--;           // decrement no of minutes by 1
	}
	
}

void stop_watch(void)
{
	seconds_ ++;                // increment the seconds by 1
}

int main (void)
{
	SYSCTL_RCGCGPIO_R |= 0x3F; //enable the clk to all the used ports
        Buzzer_init();            // initialize the registers of the buzzer in the main code
	init();
 	LCD_init();              // initialize the registers of the LCD in the main code
	keypad_Init();          // initialize the registers of the keypad in the main code
	Timer0A_Init();         // initialize the registers of the timer0A in the main code
	Timer0_SetCallBack(Timer_mode);  // call back function has the address of the timer mode function
	Timer1A_Init();         // initialize the registers of the timer1A in the main code
	Timer1_SetCallBack(stop_watch); // call back function has the address of the stop watch function
	SYSCTL_RCGCGPIO_R |= 0x20; 
	while((SYSCTL_PRGPIO_R& 0x20) == 0){};
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_DIR_R &=~ (1<<4)|~(1<<0) |~(1<<1); // set the push buttons direction
	GPIO_PORTF_PUR_R |= (1<<4)|(1<<0)|(1<<1);   // set the push buttons to be pull-up
	GPIO_PORTF_DEN_R= (1<<4)|(1<<1)|(1<<0);     // and finally set the push buttons to be enabled 

	while(1)
	{
		if(flag==0)  // first mode, calculator
		{
                    while(flag==0)
                    {
                      
			delay_ms(1000);
			LCD_Print("Enter num1:"); // display on the lcd to enter number 1
			delay_ms(1000);
			LCD_Clear();
			do{            //to be sure that the user really entered a key.
				key_1= keypad_getkey();
				delay_ms(500);   //wait for the debounce
				if (key_1 >= '0' && key_1 <='9') // doesnt accept any thing rather than digits
				{
					LCD_Show(key_1);
					num_1[i]=(key_1-48); // store it as a number in the array
					i++;   //increment the index
					c1++;  // increment the variable for knowing the digit becomes after its place to display
				}
				if ((key_1=='$' && i==0)) // if the user doesnt enter any no it would not be accepted "error"

				{ 
					delay_ms(500);
					LCD_Clear();
					LCD_Print("Plz enter no :");  // ask the user once more to enter a number
					delay_ms(500);
					LCD_Clear ();  
				}
                               

			}while((key_1!='$')&& (i>0));  // stay in the while loop till the user press enter but he has to enter the no

			num1 = storing (num_1 ,i); // storing it in a global variable known as no
			i=0; // clear the index

			LCD_Print("Enter oper:");  // ask the user to enter the operation
			delay_ms(1500);
			LCD_Clear();

			do
			{
				delay_ms(200); 
				key_1= keypad_getkey();  // wait the user to enter the operation
				if (key_1 == '+')      
				{
					LCD_Show('+');
					delay_ms(1000);
					LCD_Clear();
					operation = '+';  // make the operation to be plus 
					delay_ms(150);
					break; 
				}

				else if (key_1 == '-')
				{
					LCD_Show('-');
					delay_ms(1500);
					LCD_Clear();
					operation = '-';  // make the operation to be minus
					delay_ms(150);
					break;
				}

				else if (key_1 == '*')
				{
					LCD_Show('*');
					delay_ms(1500);
					LCD_Clear();
					operation = '*';  // make the operation to be times
					delay_ms(150);
					break;  
				}

				else if (key_1 == '/')
				{
					LCD_Show('/');
					delay_ms(1500);
					LCD_Clear();
					operation = '/'; // make the operation to be divided
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
			//num_2[9]={0};
			LCD_Clear();
			LCD_Cursor(0, 1);
			LCD_Write_Integer(num1);
			LCD_Cursor(0, (c1+1));  //know the place where it would display
			LCD_Show(operation);
			LCD_Cursor(0, (c1+3));
			LCD_Write_Integer(num2);
			delay_ms(1500);

			key_1 = keypad_getkey();
			delay_ms(200);   //wait for the debounce

			if (key_1 == '=')
			{
				LCD_Cursor(1, 0);
				LCD_Show(key);
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
                        break;
                    }
		}

	else if(flag==1)
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
		//LCD_Cursor(0,2);
		LCD_Show(':');
		delay_ms (30);
		seconds1=keypad_getkey();

		if(seconds1-48>5)
		{
			LCD_Print("ERROR");
			LCD_Clear();
			minutes1=keypad_getkey();
			LCD_Show (minutes1);
			//delay_ms (1000);
			minutes2=keypad_getkey();
			LCD_Show(minutes2);
			//delay_ms (1000);
			//LCD_Cursor(0,3);
			LCD_Show(':');
			//delay_ms (1000);
			seconds1=keypad_getkey();
		}
		else
		{
			//LCD_Cursor(0,4);
			LCD_Show(seconds1);  
			//delay_ms (1000);      
		}

		seconds2=keypad_getkey();
		//LCD_Cursor(0,5);
		LCD_Show (seconds2);
		delay_ms (30);
		minutes=(((minutes1-48)*10)+(minutes2-48));  // convert the two characters of the minutes into an integar
		seconds=(((seconds1-48)*10)+(seconds2-48));  // convert the two characters of the seconds into an integar

		while (key != '$') 
		{
			key=keypad_getkey();
		}
		LCD_Clear();
		TIMER0_CTL_R = 0x01;    

		while(flag==2)
		{
			LCD_Cursor(0,0);
			LCD_Write_Integer(minutes);
			//LCD_Cursor(0,3);
			LCD_Show(':');
                        if ( seconds<10)
                        {
                          //LCD_Cursor(0,5);
                          LCD_Write_Integer(0);
			  LCD_Write_Integer(seconds); 
                        }
                        else
                        {
                          //LCD_Cursor(0,4);
			  LCD_Write_Integer(seconds); 
                        }
                      
		}
                break;
	}
	else if(flag==2)  // enter the last mode, the stop watch
	{
		LCD_Write_Integer(minutes_); // display minutes 
		LCD_Write_Integer(minutes_);
		LCD_Show (':');
		LCD_Write_Integer(seconds_); // display seconds
		LCD_Write_Integer(seconds_);
		LCD_Cursor (0,2);
		LCD_Command(0x0c);

		while(flag==2) 
		{
			if(((GPIO_PORTF_DATA_R &(0x10))==0)) //START push button is pressed
			{
				TIMER1_CTL_R |= 0x01; // enable the control register
				while((TIMER1_CTL_R == 0x01) && ((GPIO_PORTF_DATA_R &(0x01))!=0) && ((GPIO_PORTF_DATA_R &(0x02))!=0)) 
				{
                                      // as the control register is enabled and the reset and pause push buttons are not pressed 
					if (seconds_ < 10) 
					{
						//seconds_ ++;
						LCD_Cursor(0,4); //cursor 4 m,esh 5
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
			else if((GPIO_PORTF_DATA_R &(0x01))==0) //PAUSE  push button is pressed
			{
				TIMER1_CTL_R = 0;	// disable the timer control register
			}
			else if((GPIO_PORTF_DATA_R &(0x02))==0) //RESET push button is pressed
			{
				seconds_ =0;    //seconds become equal zero
				minutes_=0;     //minutess become equal zero
				LCD_Cursor(0,0);
				LCD_Write_Integer(minutes_); //display the minutes( 00)
				LCD_Cursor(0,1);
				LCD_Write_Integer(minutes_);
				LCD_Cursor(0,3);
				LCD_Write_Integer(seconds_); //display the seconds( 00)
				LCD_Cursor(0,4);
				LCD_Write_Integer(seconds_);
				TIMER1_CTL_R &= ~(0x01);

			}

		}  
                break;
	}
}
}
