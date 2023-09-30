#include "Switch_Button.h"

int flag=0;

void Switch_Button_init(void)
{
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R=0x10;
  GPIO_PORTF_PUR_R |= (1<<4);
  GPIO_PORTF_DIR_R &= ~(1<<4); 
  GPIO_PORTF_DEN_R|= (1<<4); 

  NVIC_EN0_R|= (1<<30); 
  GPIO_PORTF_IS_R  = 0x00;     // edge  
  GPIO_PORTF_IBE_R = 0x00; 
  GPIO_PORTF_IEV_R = 0x00;        //negative edge
  GPIO_PORTF_ICR_R |= (1<<4) ;    // Clear the raw interruot register
  GPIO_PORTF_IM_R  |= (1<<4);
}

void GPIOF_Handler(void)
{
  flag++;
  if(flag>2)
  {
    flag=0;
  }
  delay_ms(500);
  GPIO_PORTF_ICR_R|=(1<<4);
}
