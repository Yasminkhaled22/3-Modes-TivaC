#include "Buzzer.h"
#include "tm4c123gh6pm.h"

void Buzzer_init()
{
    SYSCTL_RCGCGPIO_R |= 0x40;

  	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R|=0x04;
        GPIO_PORTF_DIR_R |= (1<<2); 
        GPIO_PORTF_DEN_R|=(1<<2);  
}
void Buzzer_on(void)
{	
  GPIO_PORTF_DATA_R|=(1<<2); 

}
void Buzzer_off(void)
{
    GPIO_PORTF_DATA_R&=~(1<<2); 

}