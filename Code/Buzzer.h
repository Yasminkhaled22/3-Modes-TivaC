#ifndef Buzzer_H_
#define Buzzer_H_
#include "types.h"
#include "DIO.h"

#define BUZZER_PORT             PORTF_ID
#define BUZZER_PIN              PIN2_ID

void Buzzer_init();
void Buzzer_off();
void Buzzer_on();

#endif
