#include "GLCD.h"
#include "GUI.h"
#include <stdlib.h>
#include <lpc17xx.h>
#include "cmsis_os2.h"
#include "type_declarations.h"
#include <stdbool.h>
#include "pushbutton.h"
#include "enemy.h"


#define MAINMENU 0
#define LEVEL1 1
#define LEVEL2 2
#define COMPLETE 3

uint8_t sel_lev;
osMutexId_t game_state_id;
uint8_t game_state;
//need to make the ISR for button press below is a temp variable to store the button press


void GUI_Start(void){
	GLCD_Init();
	GLCD_Clear(Blue);
	//no need mutex here because only the GUI tasks will access it
	sel_lev = 1;
	GLCD_DisplayString(14, 18, 0, "  Level 1");
	GLCD_DisplayString(18, 18, 0, "  Level 2");
	GLCD_DisplayChar(14,18,0,'>');
	game_state_id = osMutexNew(NULL);
	game_state = MAINMENU;//no need mutex as the threads have not started yet
}


void GUI_Task(void *arg){
	while(true){
		if(game_state == MAINMENU){
			GUI_Level_Menu();
		}
		else if (game_state == LEVEL1){
			GUI_Level_1();
			GLCD_DisplayString(20,20,0,"LEVEL 1 PLACEHOLDER");
			//do stuff for level 1 GUI
		}
		else if (game_state == LEVEL2){
			GLCD_DisplayString(20,20,0,"LEVEL 2 PLACEHOLDER");
			//do stuff for level 2 GUI
		}	
		else if (game_state == COMPLETE)
	}
}


void GUI_Level_1(void){
	GLCD_Bitmap(/*pass it in here*/);
	while(game_state == LEVEL1){
		osMutexAcquire()
			for (int i = 0; i < NUM_OF_ENEMIES; i++) {
				GLCD_Bitmap(enemies[i]->x, enemies[i]->y, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_BITM)
				//this probably needs to be animate instead			
			}
		os
	}
	//load background bitmap
	//load enimies
	//load main character

}



void GUI_Level_Menu(void){
	
	bool level_changed = false;
	osMutexAcquire(joy_val_id,osWaitForever);
	if(joy_in->down > joy_in->up){
		joy_in->down = 0;
		joy_in->up = 0;
		joy_in->left = 0;
		joy_in->right = 0;//maybe make this all into a function
		sel_lev = 2;
		level_changed = true;
	}
	else if (joy_in->up > joy_in->down){
		joy_in->down = 0;
		joy_in->up = 0;
		joy_in->left = 0;
		joy_in->right = 0;//maybe make this all into a function
		sel_lev = 1;
		level_changed = true;
	}
	osMutexRelease(joy_val_id);
	
	if(level_changed) {
		if (sel_lev == 1){
			GLCD_DisplayString(18, 18, 0, "  Level 2");
			GLCD_DisplayChar(14,18,0,'>');
		}
		else{
			GLCD_DisplayString(14, 18, 0, "  Level 1");
			GLCD_DisplayChar(18,18,0,'>');
		}	
	}
	
	if (button_pushed){
		button_pushed = false;
		GLCD_Clear(Black);
		if(sel_lev == 1){
			game_state = LEVEL1;
		}
		else{
			game_state = LEVEL2;
		}
	}	
}
