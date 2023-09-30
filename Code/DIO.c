#include "bitwise.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"

void DIO_Init(uint8 PORT_ID)
{
    SYSCTL_RCGCGPIO_R |= (1<<PORT_ID); // activating the clock of the MCU to Ports
    while((SYSCTL_PRGPIO_R&(1<<PORTF_ID)) == 0){};
  
  switch(PORT_ID)
  {
  case PORTA_ID:
    {
      GPIO_PORTA_LOCK_R = 0x4C4F434B;
      GPIO_PORTA_CR_R = 0xFF;               
      GPIO_PORTA_DEN_R = 0x1F;
      GPIO_PORTA_PUR_R= 0x11;

      break;
    }
  case PORTB_ID:
    {
      GPIO_PORTB_LOCK_R = 0x4C4F434B;
      GPIO_PORTB_CR_R = 0xFF;
      GPIO_PORTB_DEN_R = 0x1F;
      GPIO_PORTB_PUR_R= 0x11;
      break;
    }
  case PORTC_ID:
    {
      GPIO_PORTC_LOCK_R = 0x4C4F434B;
      GPIO_PORTC_CR_R = 0xFF;
      GPIO_PORTC_DEN_R = 0x1F;
      GPIO_PORTC_PUR_R= 0x11;
      break;
    }
  case PORTD_ID:
    {
      GPIO_PORTD_LOCK_R = 0x4C4F434B;
      GPIO_PORTD_CR_R = 0xFF;
      GPIO_PORTD_DEN_R = 0x1F;
      GPIO_PORTD_PUR_R= 0x11;
      break;
    }
  case PORTE_ID:
    {
      GPIO_PORTE_LOCK_R = 0x4C4F434B;
      GPIO_PORTE_CR_R = 0x3F;
      GPIO_PORTE_DEN_R = 0x1F;
      GPIO_PORTE_PUR_R= 0x11;
      break;
    }
  case PORTF_ID:
    {
      GPIO_PORTF_LOCK_R = 0x4C4F434B;
      GPIO_PORTF_CR_R = 0x1F;
      GPIO_PORTF_DEN_R = 0x1F;
      GPIO_PORTF_PUR_R= 0x11;
      break;
    }
  }


}
void DIO_setupPinDirection(uint8 PORT_ID, uint8 PIN_ID, DIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
  if((PIN_ID >= NUM_OF_PINS_PER_PORT) || (PIN_ID >= NUM_OF_PORTS))
  {
          /* Do Nothing */
  }
  else
  {
          /* Setup the pin direction as required DDR*/
    switch(PORT_ID)
    {
    case PORTA_ID:
      if(direction == PIN_OUTPUT)
      {
              SET_BIT(GPIO_PORTA_DIR_R,PIN_ID);
      }
      else
      {
              CLEAR_BIT(GPIO_PORTA_DIR_R,PIN_ID);
      }
      break;
    case PORTB_ID:
      if(direction == PIN_OUTPUT)
      {
              SET_BIT(GPIO_PORTB_DIR_R,PIN_ID);
      }
      else
      {
              CLEAR_BIT(GPIO_PORTB_DIR_R,PIN_ID);
      }
      break;
    case PORTC_ID:
      if(direction == PIN_OUTPUT)
      {
              SET_BIT(GPIO_PORTC_DIR_R,PIN_ID);
      }
      else
      {
              CLEAR_BIT(GPIO_PORTC_DIR_R,PIN_ID);
      }
      break;
    case PORTD_ID:
      if(direction == PIN_OUTPUT)
      {
              SET_BIT(GPIO_PORTD_DIR_R,PIN_ID);
      }
      else
      {
              CLEAR_BIT(GPIO_PORTD_DIR_R,PIN_ID);
      }
      break;
    case PORTE_ID:
      if(direction == PIN_OUTPUT)
      {
              SET_BIT(GPIO_PORTE_DIR_R,PIN_ID);
      }
      else
      {
              CLEAR_BIT(GPIO_PORTE_DIR_R,PIN_ID);
      }
      break;
    case PORTF_ID:
      if(direction == PIN_OUTPUT)
      {
              SET_BIT(GPIO_PORTF_DIR_R,PIN_ID);
      }
      else
      {
              CLEAR_BIT(GPIO_PORTF_DIR_R,PIN_ID);
      }
      break;                        
    }
  }
}
void DIO_WritePin( uint8 PORT_ID,uint8 PIN_ID, uint8 value)
{
  switch (PORT_ID)
  {
  case PORTA_ID :
    {
        SET_BIT (GPIO_PORTA_DEN_R,PIN_ID);
        SET_BIT (GPIO_PORTA_DIR_R,PIN_ID);
      if (value==1)
      {
        SET_BIT (GPIO_PORTA_DATA_R,PIN_ID);
      }
      else 
      {
        CLEAR_BIT (GPIO_PORTA_DATA_R, PIN_ID);
      }
          break;

    }
      case PORTB_ID :
    {
      SET_BIT (GPIO_PORTB_DEN_R,PIN_ID);
      SET_BIT (GPIO_PORTB_DIR_R,PIN_ID);
      if (value==1)
      {
        SET_BIT (GPIO_PORTB_DATA_R,PIN_ID);
      }
      else 
      {
        CLEAR_BIT (GPIO_PORTB_DATA_R, PIN_ID);
      }
          break;

    }
      case PORTC_ID :
    {
      SET_BIT (GPIO_PORTC_DEN_R,PIN_ID);
      SET_BIT (GPIO_PORTC_DIR_R,PIN_ID);

      if (value==1)
      {
        SET_BIT (GPIO_PORTC_DATA_R,PIN_ID);
      }
      else 
      {
        CLEAR_BIT (GPIO_PORTC_DATA_R, PIN_ID);
      }
          break;

    }
      case PORTD_ID :
    {    
      SET_BIT (GPIO_PORTD_DEN_R,PIN_ID);
      SET_BIT (GPIO_PORTD_DIR_R,PIN_ID);
      if (value==1)
      {
        SET_BIT (GPIO_PORTD_DATA_R,PIN_ID);
      }
      else 
      {
        CLEAR_BIT (GPIO_PORTD_DATA_R, PIN_ID);
      }
          break;

    }
      case PORTE_ID :
    {
      SET_BIT (GPIO_PORTE_DEN_R,PIN_ID);
      SET_BIT (GPIO_PORTE_DIR_R,PIN_ID);      
      if (value==1)
      {
        SET_BIT (GPIO_PORTE_DATA_R,PIN_ID);
      }
      else 
      {
        CLEAR_BIT (GPIO_PORTE_DATA_R, PIN_ID);
      }
          break;

    }
      case PORTF_ID :
    {
      SET_BIT (GPIO_PORTF_DEN_R,PIN_ID);
      SET_BIT (GPIO_PORTF_DIR_R,PIN_ID);
      if (value==1)
      {
        SET_BIT (GPIO_PORTF_DATA_R,PIN_ID);
      }
      else 
      {
        CLEAR_BIT (GPIO_PORTF_DATA_R, PIN_ID);
      }
         break;
 
    }
    
  }
}

void DIO_WritePort(uint8 PORT_ID,  uint8 DIR,uint8 value)
{
  switch(PORT_ID)
  {
    case PORTA_ID:
    GPIO_PORTA_DIR_R=DIR;
    GPIO_PORTA_DATA_R=value;
    break; 
    
    case PORTB_ID:
    GPIO_PORTB_DIR_R=DIR;
    GPIO_PORTB_DATA_R=value;
    break;
    
    case PORTC_ID:
    GPIO_PORTC_DIR_R=DIR;
    GPIO_PORTC_DATA_R=value;
    break;
    
    case PORTD_ID:
    GPIO_PORTD_DIR_R=DIR;
    GPIO_PORTD_DATA_R=value;
    break;
    
    case PORTE_ID:
    GPIO_PORTE_DIR_R=DIR;
    GPIO_PORTE_DATA_R=value;
    break;
    
    case PORTF_ID:
    GPIO_PORTF_DIR_R=DIR;
    GPIO_PORTF_DATA_R=value;
    break;
  }
    
}

uint8 DIO_readPin(uint8 PORT_ID, uint8 PIN_ID)		
{
  uint8 read_value;
  switch(PORT_ID)
  {
    case PORTA_ID:
  
    if(GET_BIT(GPIO_PORTA_DATA_R,PIN_ID))
    read_value=(GET_BIT(GPIO_PORTA_DATA_R,PIN_ID));
    break; 
    
    case PORTB_ID:
    read_value=(GET_BIT(GPIO_PORTB_DATA_R,PIN_ID));
    break;
    
    case PORTC_ID:
    read_value=(GET_BIT(GPIO_PORTC_DATA_R,PIN_ID));
    break;
    
    case PORTD_ID:
    read_value=(GET_BIT(GPIO_PORTD_DATA_R,PIN_ID));
    break;
    
    case PORTE_ID:
    read_value=(GET_BIT(GPIO_PORTE_DATA_R,PIN_ID));
    break;
    
    case PORTF_ID:
    read_value=(GET_BIT(GPIO_PORTF_DATA_R,PIN_ID));
    break;
  }
  return read_value;
}

uint8 DIO_readPort(uint8 PORT_ID)		
{
  uint8 read_port;
  switch(PORT_ID)
  {
    case PORTA_ID:
  
    read_port=GPIO_PORTA_DATA_R;
    break; 
    
    case PORTB_ID:
    read_port=GPIO_PORTB_DATA_R;
    break;
    
    case PORTC_ID:
    read_port=GPIO_PORTC_DATA_R;
    break;
    
    case PORTD_ID:
    read_port=GPIO_PORTD_DATA_R;
    break;
    
    case PORTE_ID:
    read_port=GPIO_PORTE_DATA_R;
    break;
    
    case PORTF_ID:
    read_port=GPIO_PORTF_DATA_R;
    break;
  }
  return read_port;
}

/*void delay_ms(int32 counter)
{
  while(counter>0)
    counter--;
}*/

