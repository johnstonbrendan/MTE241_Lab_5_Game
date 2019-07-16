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


// Level Definitions
#define NUM_LEVELS 2
#define MAINMENU 0
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL1_COMPLETE 3
#define LEVEL2_COMPLETE 4


#define NUM_FLOORS 10

uint8_t sel_lev;
osMutexId_t game_state_id;
uint8_t game_state;
//need to make the ISR for button press below is a temp variable to store the button press

const int8_t left_offset[NUM_LEVELS][NUM_FLOORS] = {
	{0, -1, -1, 2, -1, 1, -1, 0, -1, -1}, 
	{0, -1, 1, -1, -1, 2, -1, 3, -1, -1}
};

const int8_t right_offset[NUM_LEVELS][NUM_FLOORS] = {
	{0, -1, -1, 0, -1, 2, -1, 1, -1, -1},
	{4, -1, 1, -1, -1, 3, -1, 0, -1, -1} 
};

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
		else if (game_state == LEVEL1_COMPLETE){
			GLCD_Clear(Green);
			GLCD_DisplayString(20,20,0,"Congrats yo yo you did it!!!!! nOW TRY LEVEL 2 :)");
		}
		else if (game_state == LEVEL2_COMPLETE){
			GLCD_Clear(Red);
			GLCD_DisplayString(20,20,0,"Congrats yoU COMPLETED LEVEL 2");
		}
	}
}


void GUI_Level_1(void){
	drawBackground(1);//include end goal in the background
	while(game_state == LEVEL1){
			animate_player();
			for (int i = 0; i < NUM_OF_ENEMIES; i++) {
				animate_enemy(enemies[i]);
			}
			animate_collisions();//collision will handle both hitting an enemy and getting to the end goal
			//end point stored in bitmaps.h
	}
}

void animate_enemy(char_info_t* enemy){
	osMutexAcquire(enemy_loc_id,osWaitForever);
	//GLCD_Bitmap(enemy.pos->x, enemy.pos->y,ENEMY_WIDTH,ENEMY_HEIGHT,NULL);
	//GLCD_Bitmap(100,100,ENEMY_WIDTH,ENEMY_HEIGHT,BMP_ENEMY_DATA);
	enemy->pos.x = enemy->pos.x + enemy->delta.x;
	enemy->pos.y = enemy->pos.y + enemy->delta.y;
	enemy->delta.x = 0;
	enemy->delta.y = 0; //maybe make all this into a function
//	GLCD_Bitmap(0,0,30,30,BMP_ENEMY_DATA);
	GLCD_Bitmap(enemy->pos.x,enemy->pos.y,ENEMY_WIDTH,ENEMY_HEIGHT,BMP_ENEMY_DATA);//this should be replaced with an animate function
	osMutexRelease(enemy_loc_id);

}


void animate_player(void){
	osMutexAcquire(player_loc_id,osWaitForever);
	if (!player_info->teleport){//do the common animation
		player_info->pos.x = player_info->pos.x + player_info->delta.x;
		player_info->pos.y = player_info->pos.y + player_info->delta.y;
		player_info->delta.x = 0;
		player_info->delta.y = 0; //maybe make all this into a function
	//	GLCD_Bitmap(0,0,30,30,BMP_ENEMY_DATA);
		//handle respawning then set teleport back to false
		//need to make the below thing an animation
		GLCD_Bitmap(player_info->pos.x,player_info->pos.y,ENEMY_WIDTH,ENEMY_HEIGHT,BMP_ENEMY_DATA);//needs to change for player
	}
	else
	{
		player_info->delta.x = 0;
		player_info->delta.y = 0;
		player_info->teleport = false;
		player_info->pos.x = PLAYER_INIT_X;
		player_info->pos.y = PLAYER_INIT_Y;
		//need to add in some thing that does not animate and instantly moves the player
		GLCD_Bitmap(player_info->pos.x,player_info->pos.y,ENEMY_WIDTH,ENEMY_HEIGHT,BMP_ENEMY_DATA);//needs to change for player
	}
	osMutexRelease(player_loc_id);
}

void animate_collisions(void){
	uint16_t player_x, player_y = 0;
	bool collision = false;
	osMutexAcquire(player_loc_id,osWaitForever);
	player_x = player_info->pos.x;
	player_y = player_info->pos.y;
	osMutexRelease(player_loc_id);
	osMutexAcquire(enemy_loc_id,osWaitForever);
	for (int i = 0; i < NUM_OF_ENEMIES; i++){
		if ((enemies[i]->pos.y > player_y) && (enemies[i]->pos.y < player_y + PLAYER_HEIGHT)){ 
			//this is when the collision occurs on the right or left sides (above checks they are on the same level)(then below checks if there is collision)
			if ((enemies[i]->pos.x < player_x + PLAYER_WIDTH) && (enemies[i]->pos.x > player_x)){ 
				collision = true;
			}
			//some of this if stuff (above and below) might be able to be simplified so that you don't have to add enemy_width and player width
			else if ((enemies[i]->pos.x + ENEMY_WIDTH > player_x) && (enemies[i]->pos.x + ENEMY_WIDTH < player_x + PLAYER_WIDTH)){
				collision = true;
			}
		}
		else if ((enemies[i]->pos.x > player_x) && (enemies[i]->pos.x < player_x + PLAYER_WIDTH)){
			//this is a collision occuring from the top
			if ((enemies[i]->pos.y + ENEMY_HEIGHT > player_y) && (enemies[i]->pos.y < player_y)){
				collision = true;
			}
			else if ((enemies[i]->pos.y < player_y + ENEMY_HEIGHT) && (enemies[i]->pos.y > player_y)){
				collision = true;
			}
		}
		if (collision){
			break;
		}//should have only one collision
	}
	osMutexRelease(enemy_loc_id);
	if (collision){
		osMutexAcquire(player_loc_id, osWaitForever);
		player_info->teleport = true;
		player_info->pos.x = PLAYER_INIT_X;
		player_info->pos.y = PLAYER_INIT_Y;
		osMutexRelease(player_loc_id);
		// do stuff to handle collision like acquiring the mutexes and then teleporting the player back to the original space
	}
	if ((player_x == END_X) && (player_y == END_Y)){//this may need to be similiar to collision above instead of just the x,y
		osMutexAcquire(game_state_id,osWaitForever);
		game_state = LEVEL1_COMPLETE;
		osMutexRelease(game_state_id);
	}
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

void drawBackground(uint8_t level){ 
	if(level > NUM_LEVELS) {
		GLCD_DisplayString(0, 0, 1, "Invalid lvl drawbg!");
		for(;;); // get stuck here for debugger!
	}
	level--;
	uint16_t startPixel, endPixel = 0;
	for(uint8_t i = 0; i < NUM_FLOORS; i++) {
		if(left_offset[level][i] >= 0 && right_offset[level][i] >= 0) {
			startPixel = left_offset[level][i]*BMP_GRASSBLOCK_WIDTH;
			endPixel = SC_WIDTH - right_offset[level][i]*BMP_GRASSBLOCK_WIDTH;
			for(uint16_t j = startPixel; j < endPixel; j+=BMP_GRASSBLOCK_WIDTH){
				GLCD_Bitmap(j, i*BMP_GRASSBLOCK_HEIGHT, BMP_GRASSBLOCK_WIDTH, BMP_GRASSBLOCK_HEIGHT, BMP_GRASSBLOCK_DATA);
			}
		}
	}
}

bool isFloor(uint8_t level, uint16_t x, uint16_t y) { 
	if(level > NUM_LEVELS) {
		GLCD_DisplayString(0, 0, 1, "Invalid lvl isFloor!");
		for(;;); // get stuck here for debugger!
	}

	level--;
	uint16_t floor = y / BMP_GRASSBLOCK_HEIGHT - 1;
	if(floor < 0) floor = 0;
	
	if(left_offset[level][floor] < 0) return false;
	
	uint8_t blocksAwayFromLeftWall = x/BMP_GRASSBLOCK_WIDTH;
	if(left_offset[level][floor] <= blocksAwayFromLeftWall 
		&& (SC_WIDTH/BMP_GRASSBLOCK_WIDTH - right_offset[level][floor]) >= blocksAwayFromLeftWall) {
			return true;
	}

	else return false;	
}
