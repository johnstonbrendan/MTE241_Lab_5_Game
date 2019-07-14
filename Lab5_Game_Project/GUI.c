#include "GLCD.h"
#include "GUI.h"
#include <stdlib.h>
#include <lpc17xx.h>
#include "cmsis_os2.h"
#include "type_declarations.h"
#include <stdbool.h>
#include "pushbutton.h"
#include "enemy.h"
#include "bitmaps.h"
#include "player.h"
#include <math.h>



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
	//GLCD_Bitmap(0,0,320,240,background_map);
	GLCD_Clear(Blue);
	//no need mutex here because only the GUI tasks will access it
	sel_lev = 1;
	GLCD_DisplayString(14, 18, 0, "  Level 1");
	GLCD_DisplayString(18, 18, 0, "  Level 2");
	GLCD_DisplayChar(14,18,0,'>');
	game_state_id = osMutexNew(NULL);
	game_state = MAINMENU;//no need mutex as the threads have not started yet
	game_state = LEVEL1;//THIS IS ONLY HERE FOR TESTING
}


void GUI_Task(void *arg){
	while(true){
		if(game_state == MAINMENU){
			GUI_Level_Menu();
		}
		else if (game_state == LEVEL1){
			GLCD_Clear(Blue);
			GUI_Level_1();
			GLCD_DisplayString(20,20,0,"LEVEL 1 PLACEHOLDER");
			//do stuff for level 1 GUI
		}
		else if (game_state == LEVEL2){
			GLCD_DisplayString(20,20,0,"LEVEL 2 PLACEHOLDER");
			//do stuff for level 2 GUI
		}	
		else if (game_state == COMPLETE){
			GLCD_DisplayString(20,20,0,"Congrats yo yo you did it!!!!! :)");
		}
	}
}


void GUI_Level_1(void){
	//GLCD_Bitmap(/*pass it in here*/);
	while(game_state == LEVEL1){
			for (int i = 0; i < NUM_OF_ENEMIES; i++) {
				animate_enemy(enemies[i]);
			}
			animate_player();
			animate_collisions();
	}
	//load background bitmap
	//load enimies
	//load main character

}

void animate_enemy(char_info_t* enemy){
	osMutexAcquire(enemy_loc_id,osWaitForever);
	//GLCD_Bitmap(enemy.pos->x, enemy.pos->y,ENEMY_WIDTH,ENEMY_HEIGHT,NULL);
	//GLCD_Bitmap(100,100,ENEMY_WIDTH,ENEMY_HEIGHT,enemy_map);
	enemy->pos.x = enemy->pos.x + enemy->delta.x;
	enemy->pos.y = enemy->pos.y + enemy->delta.y;
	enemy->delta.x = 0;
	enemy->delta.y = 0; //maybe make all this into a function
//	GLCD_Bitmap(0,0,30,30,enemy_map);
	GLCD_Bitmap(enemy->pos.x,enemy->pos.y,ENEMY_WIDTH,ENEMY_HEIGHT,enemy_map);
	osMutexRelease(enemy_loc_id);

}


void animate_player(void){
	osMutexAcquire(player_loc_id,osWaitForever);
	player_info->pos.x = player_info->pos.x + player_info->delta.x;
	player_info->pos.y = player_info->pos.y + player_info->delta.y;
	player_info->delta.x = 0;
	player_info->delta.y = 0; //maybe make all this into a function
//	GLCD_Bitmap(0,0,30,30,enemy_map);
	GLCD_Bitmap(player_info->pos.x,player_info->pos.y,ENEMY_WIDTH,ENEMY_HEIGHT,enemy_map);//needs to change for player
	osMutexRelease(player_loc_id);
}

void animate_collisions(void){
	uint16_t player_x, player_y = 0;
	osMutexAcquire(player_loc_id,osWaitForever);
	player_x = player_info->pos.x;
	player_y = player_info->pos.y;
	osMutexRelease(player_loc_id);
	osMutexAcquire(enemy_loc_id,osWaitForever);
	for (int i = 0; i < NUM_OF_ENEMIES; i++){
		//need to adjust the y check depending on how the players and enimies are placed on the maps
		//player_x + PLAYER_WIDTH/2 represents the middle of the player, same logic applies for the enemy
		//either do below for distance or do the super long if statment for ranges
		if (dist_between_points(player_x,player_y,enemies[i]->pos.x,enemies[i]->pos.y) < PLAYER_WIDTH/2 + ENEMY_HEIGHT/2) //note this only works for SQUARE AND CIRCULAR CHARACTERS
		{
			
			//do collision stuff
		}
		
		if (check if the edge of one of the box is withing the bound of the locations of x of the other box, boxes being enemyies and players)
	}
}

uint16_t dist_between_points(uint16_t player_x, uint16_t player_y, uint16_t enemy_x, uint16_t enemy_y){
	
	//use the sqrt and power functions here
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
