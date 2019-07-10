#include <stdbool.h>

#ifndef _PUSHBUTTON_H
#define _PUSHBUTTON_H

extern bool button_pushed;

void setup_INT0(void);

void EINT3_IRQHandler(void);

#endif
