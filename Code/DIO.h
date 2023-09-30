#ifndef DIO_H_
#define DIO_H_

#include "types.h"
#define NUM_OF_PORTS           6
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3
#define PORTE_ID               4
#define PORTF_ID               5

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7


typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}DIO_PinDirectionType;

void DIO_Init(uint8 PORT_ID);
void DIO_WritePin( uint8 PORT_ID,uint8 PIN_ID, uint8 value);
void DIO_WritePort(uint8 PORT_ID,  uint8 DIR,uint8 value);
void DIO_setupPinDirection(uint8 PORT_ID, uint8 PIN_ID, DIO_PinDirectionType direction);
uint8 DIO_readPin(uint8 PORT_ID, uint8 PIN_ID);
uint8 DIO_readPort(uint8 PORT_ID);		

#endif