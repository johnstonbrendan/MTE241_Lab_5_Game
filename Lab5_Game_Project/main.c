#include <lpc17xx.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os2.h"
#include "GLCD.h"
#include "GUI.h"
#include "type_declarations.h"
#include "pushbutton.h"
#include "Joy.h"
#include "Pot.h"

osThreadId_t GUI_Thread, Pot_Thread, Joy_Thread; //... add more!

void init(void){
	GUI_Start();
	setup_INT0();
	Joy_init();
}

int main(void){
	init();
	osKernelInitialize();
	GUI_Thread = osThreadNew(GUI_Task,NULL,NULL);
	Pot_Thread = osThreadNew(Pot_Task,NULL,NULL);
	Joy_Thread = osThreadNew(Joy_Task,NULL,NULL);
	osKernelStart();
	for(;;);
}
	
	