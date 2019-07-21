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
#include "enemy.h"
#include "bitmaps.h"
#include "player.h"
#include <stdio.h>

osThreadId_t GUI_Thread, Pot_Thread, Joy_Thread, Enemy_Thread, Player_Thread; //... add more!

void init(void){
	enemy_init();
	GUI_Start();
	setup_INT0();
	Joy_init();
	player_init(PLAYER_L1_INIT_X,PLAYER_L1_INIT_Y);//start with the player at 0,0 this will need to change
}

int main(void){
	init();
	printf("Starting program...\n");
	osKernelInitialize();
	GUI_Thread = osThreadNew(GUI_Task,NULL,NULL);
	Pot_Thread = osThreadNew(Pot_Task,NULL,NULL);
	Joy_Thread = osThreadNew(Joy_Task,NULL,NULL);
	Enemy_Thread = osThreadNew(enemy_task,NULL,NULL);
	Player_Thread = osThreadNew(player_task,NULL,NULL);
	osKernelStart();
	for(;;);
}
	
	