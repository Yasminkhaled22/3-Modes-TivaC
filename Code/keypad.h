#ifndef keypad_H_
#define keypad_H_
#include "types.h"
#include "DIO.h"
#include "tm4c123gh6pm.h"
//#include "Delay.h"

#define  padRows  4
#define  padCols  4

void keypad_Init       (void);
char keypad_getkey     (void);

#endif
