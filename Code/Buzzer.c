#include "Buzzer.h"
#include "tm4c123gh6pm.h"

void Buzzer_init()
{
    SYSCTL_RCGCGPIO_R |= 0x20;

  	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R|=0x1;
        GPIO_PORTF_DIR_R |= (1<<0); 
        GPIO_PORTF_DEN_R|=(1<<0);  
        GPIO_PORTF_DATA_R&=~(1<<0); 
}
void Buzzer_on(void)
{	
  GPIO_PORTF_DATA_R|=0x1; 

	//DIO_WritePin(GPIO_PORTF_DATA_R, BUZZER_PIN, LOGIC_HIGH);

}
void Buzzer_off(void)
{
    GPIO_PORTF_DATA_R&=~(1<<0); 

	//DIO_WritePin(GPIO_PORTF_DATA_R, BUZZER_PIN, LOGIC_LOW);

}