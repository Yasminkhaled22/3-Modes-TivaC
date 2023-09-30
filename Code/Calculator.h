#ifndef Calculator_H_
#define Calculator_H_

#include "lcd.h"
#include "keypad.h"


void calculator(void);
int addition (int num1, int num2);
int subtraction (int num1, int num2);
int multiplication (int num1, int num2);
float divide (int num1, int num2);
void clear_data();
int storing(uint8 arr[],uint32 x);

#endif