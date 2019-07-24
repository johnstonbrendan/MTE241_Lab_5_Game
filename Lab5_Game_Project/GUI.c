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
#include <stdio.h>
#include "Pot.h"
#include "Joy.h"

uint8_t sel_lev;
osMutexId_t game_state_id;
uint8_t game_state;
//need to make the ISR for button press below is a temp variable to store the button press

const int8_t left_offset[NUM_LEVELS][NUM_FLOORS] = {
	{0, -1, -1, 0, -1, -1, 0, -1, -1, -1}, 
	{0, -1, -1, 0, -1, -1, -1, 0, -1, -1}
};

const int8_t right_offset[NUM_LEVELS][NUM_FLOORS] = {
	{0, -1, -1, 3, -1, -1, 0, -1, -1, -1},
	{0, -1, -1, 2, -1, -1, -1, 5, -1, -1} 
};

portal_pair_t portal_pairs[NUM_MAX_PORTALS/2];

void GUI_Start(void){
	GLCD_Init();
	//GLCD_Bitmap(0,0,320,240,background_map);
	GLCD_Clear(Blue);
	//no need mutex here because only the GUI tasks will access it
	sel_lev = 1;
	initializeTargetEnemy();
	GLCD_DisplayString(18, 25, 0, "  Level 1");
	GLCD_DisplayString(14, 25, 0, "  Level 2");
	GLCD_DisplayChar(18,33,0,'>');
	game_state_id = osMutexNew(NULL);
	game_state = MAINMENU;//no need mutex as the threads have not started yet
	//game_state = LEVEL2;//THIS IS ONLY HERE FOR TESTING
}


void GUI_Task(void *arg){
	while(true){
		if(game_state == MAINMENU){
			GUI_Level_Menu();
		}
		else if (game_state == LEVEL1){
			GLCD_Clear(Blue);//do blue for background
			player_reset();
			Joy_Reset();
			GUI_Level_1();
			if (game_state == RESET_POT){
				GUI_Reset_Pot(true);
				osMutexAcquire(game_state_id,osWaitForever);
				game_state = LEVEL1;
				osMutexRelease(game_state_id);
			}
			GLCD_DisplayString(20,20,0,"LEVEL 1 PLACEHOLDER");
			//do stuff for level 1 GUI
		}
		else if (game_state == LEVEL2){
			GLCD_Clear(Blue);
			player_reset();
			Joy_Reset();
			GUI_Level_2();
			if (game_state == RESET_POT){
				GUI_Reset_Pot(true);
				osMutexAcquire(game_state_id,osWaitForever);
				game_state = LEVEL2;
				osMutexRelease(game_state_id);
			}
			GLCD_DisplayString(20,20,0,"LEVEL 2 PLACEHOLDER");
			//do stuff for level 2 GUI
		}	
		else if (game_state == LEVEL1_COMPLETE){
			GLCD_Clear(Green);
			GLCD_DisplayString(20,20,0,"Good job noobie, now do level 2");
			break;
		}
		else if (game_state == LEVEL2_COMPLETE){
			GLCD_Clear(Red);
			GLCD_DisplayString(20,20,0,"Congrats u COMPLETED LEVEL 2");
		}
	}
}


void GUI_Level_1(void){
	drawBackground(1);//include end goal in the background
	drawPortals(1);
	uint8_t num_of_enemies = (game_state == LEVEL1) ? NUM_OF_L1_ENEMIES : NUM_OF_L2_ENEMIES;
	while(game_state == LEVEL1){
#if GOD_MODE
			animate_player();
#else
			animate_portals();
			animate_player();
			for (int i = 0; i < num_of_enemies - 1; i++) {
				animate_enemy(enemies[i], false);
			}
			animate_enemy(enemies[num_of_enemies - 1],true);//this will be the enemy you need to catch
			animate_collisions();//collision will handle both hitting an enemy and getting to the end goal
			//end point stored in bitmaps.h
#endif
	}
}

void GUI_Level_2(void){
	drawBackground(2);
	drawPortals(2);
	uint8_t num_of_enemies = (game_state == LEVEL1) ? NUM_OF_L1_ENEMIES : NUM_OF_L2_ENEMIES;
	while(game_state == LEVEL2){
#if GOD_MODE
			animate_player();
#else
			animate_portals();
			animate_player();
			for (int i = 0; i < num_of_enemies - 1; i++) {
				animate_enemy(enemies[i], false);
			}
			animate_enemy(enemies[num_of_enemies - 1],true);//this will be the enemy you need to catch
			animate_collisions();//collision will handle both hitting an enemy and getting to the end goal
			//end point stored in bitmaps.h
#endif
	}	
	
}

void animate_enemy(char_info_t* enemy, bool to_catch){
	osMutexAcquire(enemy_loc_id,osWaitForever);
	//GLCD_Bitmap(enemy.pos->x, enemy.pos->y,ENEMY_WIDTH,ENEMY_HEIGHT,NULL);
	//GLCD_Bitmap(100,100,ENEMY_WIDTH,ENEMY_HEIGHT,BMP_ENEMY_DATA);
	enemy->pos.x = enemy->pos.x + enemy->delta.x;
	enemy->pos.y = enemy->pos.y + enemy->delta.y;
	enemy->delta.x = 0;
	enemy->delta.y = 0; //maybe make all this into a function
//	GLCD_Bitmap(0,0,30,30,BMP_ENEMY_DATA);
	if (!to_catch){
		GLCD_Bitmap(enemy->pos.x,enemy->pos.y,BMP_ENEMY_WIDTH,BMP_ENEMY_HEIGHT,BMP_ENEMY_DATA);//this should be replaced with an animate function
	}
	else{
		GLCD_Bitmap(enemy->pos.x,enemy->pos.y,BMP_ENEMY_WIDTH,BMP_ENEMY_HEIGHT, BMP_TGT_ENEMY_DATA);//this needs to be the golden enemy bitmap
	}
	osMutexRelease(enemy_loc_id);
}


void animate_player(void){
	osMutexAcquire(player_loc_id,osWaitForever);
	if(GOD_MODE && (abs(player_info->delta.x) > 0 || abs(player_info->delta.y)>0)) printf("x: %d, y: %d\n", player_info->pos.x, player_info->pos.y);
	if (!player_info->teleport){//do the common an	imation
		if(abs(player_info->delta.x) > 0) togglePlayerBitmap();
		player_info->pos.x = player_info->pos.x + player_info->delta.x;
		player_info->pos.y = player_info->pos.y + player_info->delta.y;
		player_info->delta.x = 0;
		player_info->delta.y = 0; //maybe make all this into a function
		//handle respawning then set teleport back to false
		//need to make the below thing an animation
		GLCD_Bitmap(player_info->pos.x,player_info->pos.y,BMP_PLAYER_WIDTH,BMP_PLAYER_HEIGHT-BMP_COLOR_BORDER,&bmp_player_data[3*2*BMP_PLAYER_WIDTH]);// shave off top of players bitmap

	}
	else
	{
		redraw_all();
		uint16_t intended_x, intended_y = 0;
		intended_x = player_info->pos.x + player_info->delta.x;
		intended_y = player_info->pos.y + player_info->delta.y;
		player_info->teleport = false;
		//need to add in some thing that does not animate and instantly moves the player
		//over the current player position draw a background color box the same size of the player (dynamilcally create at runtime)
		//then reload all the portals
		osMutexAcquire(game_state_id,osWaitForever);
		(game_state == LEVEL1) ? drawPortals(1) : drawPortals(2);//keep in mind that this means when you hit an enemy portals will be drawn too
		osMutexRelease(game_state_id);
		//do some animating to remove the stuff at the previous position which right now is player_info->pos.x and y
		player_info->pos.x = player_info->pos.x + player_info->delta.x;
		player_info->pos.y = player_info->pos.y + player_info->delta.y;
		player_info->delta.x = 0;
		player_info->delta.y = 0;
		GLCD_Bitmap(player_info->pos.x,player_info->pos.y,BMP_PLAYER_WIDTH,BMP_PLAYER_HEIGHT,BMP_ENEMY_DATA);//needs to change for player
	}
	osMutexRelease(player_loc_id);
}


void animate_portals(void){
	uint16_t player_x, player_y = 0;
	bool player_moved, enemy_moved = false;
	osMutexAcquire(game_state_id,osWaitForever);
	uint8_t num_of_portals = (game_state == LEVEL1) ? NUM_L1_PORTALS : NUM_L2_PORTALS;
	uint8_t num_of_enemies = (game_state == LEVEL1) ? NUM_OF_L1_ENEMIES : NUM_OF_L2_ENEMIES;
	osMutexRelease(game_state_id);
	uint8_t portal_pair_col = 100;//this is means invalid for now//this will store which portal pair had the collision
	bool player_col_p1, player_col_p2 = false, enemy_col = false;
	osMutexAcquire(player_loc_id,osWaitForever);
	player_x = player_info->pos.x;
	player_y = player_info->pos.y;
	player_moved = (bool) player_info->delta.x;//if the player
	osMutexRelease(player_loc_id);
	for (int i = 0; i < num_of_portals/2; i++){
		if (!player_col_p1 && !player_col_p2){
			
			
		player_col_p1 = check_collision(player_x, player_y, portal_pairs[i].p1x,portal_pairs[i].p1y,
						BMP_PLAYER_HEIGHT, BMP_PLAYER_WIDTH, BMP_PORTAL_HEIGHT, BMP_PORTAL_WIDTH);
		if (player_col_p1){
			portal_pair_col = i;
			//GLCD_DisplayString(0,0,1,"Hit portal p1        ");
		}
		player_col_p2 = check_collision(player_x, player_y, portal_pairs[i].p2x,portal_pairs[i].p2y,
									BMP_PLAYER_HEIGHT, BMP_PLAYER_WIDTH, BMP_PORTAL_HEIGHT, BMP_PORTAL_WIDTH);
		if (player_col_p2){
			portal_pair_col = i;
			//GLCD_DisplayString(0,0,1,"Hit portal p2          ");
		}
	}
		osMutexAcquire(enemy_loc_id,osWaitForever);
		for (int j = 0; j < num_of_enemies; j++){
			if (!enemy_moved){
				enemy_moved = (bool) (enemies[j]->delta.x + enemies[j]->delta.y);
				//GLCD_DisplayString(1,0,1,"Enemy Not Moved");
			}
			else{
												//GLCD_DisplayString(1,0,1,"Enemy Moved      ");
			}
			if (!enemy_col){// these means no need to check any other portals for enemies collisions once one has happened
					enemy_col = check_collision(enemies[j]->pos.x, enemies[j]->pos.y, 
								portal_pairs[i].p1x,portal_pairs[i].p1y, 
								BMP_ENEMY_HEIGHT, BMP_ENEMY_WIDTH, BMP_PORTAL_HEIGHT, BMP_PORTAL_WIDTH);
					enemy_col = enemy_col || check_collision(enemies[j]->pos.x, enemies[j]->pos.y, 
								portal_pairs[i].p2x,portal_pairs[i].p2y, 
								BMP_ENEMY_HEIGHT, BMP_ENEMY_WIDTH, BMP_PORTAL_HEIGHT, BMP_PORTAL_WIDTH);
				//if (enemy_col) break;//this means no need to check any other enemies
			}
		}
		osMutexRelease(enemy_loc_id);
	}
//				if (enemy_col){
//				GLCD_DisplayString(0,0,1,"Enemy Collision               ");
//				//break;//do enemy and portal collision
//			}
//			else{
//								GLCD_DisplayString(0,0,1,"No Enemy Collision             ");

//			}
	if (player_col_p1 || player_col_p2){// the user is colliding with a portal
		if (button_pushed){//if the user wants to teleport
			button_pushed = false;
			osMutexAcquire(player_loc_id,osWaitForever);
			player_info->teleport = true;
			if (player_col_p1){
				player_info->delta.x = portal_pairs[portal_pair_col].p2x - player_info->pos.x;
				player_info->delta.y = portal_pairs[portal_pair_col].p2y - player_info->pos.y;
			}
			else if(player_col_p2){
				player_info->delta.x = portal_pairs[portal_pair_col].p1x - player_info -> pos.x;
				player_info->delta.y = portal_pairs[portal_pair_col].p1y - player_info -> pos.y;
			}
			osMutexRelease(player_loc_id);
			osDelay(100); // osKernelGetSysTimerFreq not working, 100 works ok but kinda hacky
		}else if (player_moved){//player and portal are overlapping and need to redraw a part of the portal and the player has moved
			(game_state == LEVEL1) ? drawPortals(1) : drawPortals(2);
		}
	} 
	
	button_pushed = false;
	if (enemy_col && enemy_moved){
			(game_state == LEVEL1) ? drawPortals(1) : drawPortals(2);
		//GLCD_DisplayString(2,0,1,"Redraw Portals      ");
	}
}

void animate_collisions(void){
	uint16_t player_x, player_y = 0;
	bool collision,golden_enemy = false;
	uint8_t num_of_enemies = (game_state == LEVEL1) ? NUM_OF_L1_ENEMIES : NUM_OF_L2_ENEMIES;
	osMutexAcquire(player_loc_id,osWaitForever);
	player_x = player_info->pos.x;
	player_y = player_info->pos.y;
	osMutexRelease(player_loc_id);
	osMutexAcquire(enemy_loc_id,osWaitForever);
	for (int i = num_of_enemies - 1; i >= 0; i--){
		collision = check_collision(player_x, player_y, enemies[i]->pos.x, enemies[i]->pos.y,
							PLAYER_HEIGHT,PLAYER_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH);
		if (collision){
			if(i == num_of_enemies - 1){
				golden_enemy = true;
			}
			break;
		}//should have only one collision
	}
	osMutexRelease(enemy_loc_id);
	if (golden_enemy){//this may need to be similiar to collision above instead of just the x,y
		osMutexAcquire(game_state_id,osWaitForever);
		game_state = (game_state == LEVEL1) ? LEVEL1_COMPLETE: LEVEL2_COMPLETE;
		osMutexRelease(game_state_id);
	}
	if (collision && !golden_enemy){
		osMutexAcquire(player_loc_id, osWaitForever);
		player_info->teleport = true;
		player_info->delta.x = (game_state == LEVEL1) ? PLAYER_L1_INIT_X - player_info->pos.x : PLAYER_L2_INIT_X - player_info->pos.x;
		player_info->delta.y = (game_state == LEVEL1) ? PLAYER_L1_INIT_Y - player_info->pos.y : PLAYER_L2_INIT_Y - player_info->pos.y;
		osMutexRelease(player_loc_id);
		osMutexAcquire(game_state_id,osWaitForever);
		game_state = RESET_POT;
		osMutexRelease(game_state_id);
		// do stuff to handle collision like acquiring the mutexes and then teleporting the player back to the original space
	}
}

bool check_collision(uint16_t object_1_x, uint16_t object_1_y, uint16_t object_2_x, uint16_t object_2_y, 
						uint8_t object_1_h, uint8_t object_1_w, uint8_t object_2_h, uint8_t object_2_w){
		if ((object_2_y + object_2_h > object_1_y) && (object_2_y < object_1_y + object_1_h)){ 
		//this is when the collision occurs on the right or left sides (above checks they are on the same level)(then below checks if there is collision)
			if ((object_2_x < object_1_x + object_1_w) && (object_2_x > object_1_x)){ 
				return true;//bottom right
			}
			//some of this if stuff (above and below) might be able to be simplified so that you don't have to add enemy_width and player width
			else if ((object_2_x + object_2_w > object_1_x) && (object_2_x + object_2_w < object_1_x + object_1_w)){
				return true; //bottom left
			}
	}
	//else if ((object_2_x > object_1_x) && (object_2_x < object_1_x + object_1_w)){
	else if ((object_2_x + object_2_w > object_1_x) && (object_2_x < object_1_x + object_1_w)){
		//this is a collision occuring from the top
		if ((object_2_y + object_2_h > object_1_y) && (object_2_y < object_1_y)){
			return true; //top right
		}
		else if ((object_2_y < object_1_y + object_1_h) && (object_2_y > object_1_y)){
			return true; //top left
		}
	}
	return false;
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
			GLCD_DisplayString(14, 25, 0, "  Level 2");
			GLCD_DisplayChar(18,33,0,'>');
		}
		else{
			GLCD_DisplayString(18, 25, 0, "  Level 1");
			GLCD_DisplayChar(14,33,0,'>');
		}	
	}
	
	if (button_pushed){
		osDelay(200);
		button_pushed = false;
		GLCD_Clear(Black);
		osMutexAcquire(game_state_id,osWaitForever);
		if(sel_lev == 1){
			game_state = LEVEL1;
		}
		else{
			game_state = LEVEL2;
		}
		osMutexRelease(game_state_id);
		GUI_Reset_Pot(false);
		osDelay(500); // kinda hacky
	}	
}

void drawBackground(uint8_t level){ 
	if(level > NUM_LEVELS) {
		GLCD_DisplayString(0, 0, 0, "Invalid lvl drawbg!");
		for(;;); // get stuck here for debugger!
	}
	level--;
	uint16_t startPixel, endPixel = 0;
	for(uint8_t i = 0; i < NUM_FLOORS; i++) {
		if(left_offset[level][i] >= 0 && right_offset[level][i] >= 0) {
			startPixel = right_offset[level][i]*BMP_GRASSBLOCK_WIDTH;
			endPixel = SC_WIDTH - left_offset[level][i]*BMP_GRASSBLOCK_WIDTH;
			for(uint16_t j = startPixel; j < endPixel; j+=BMP_GRASSBLOCK_WIDTH){
				GLCD_Bitmap(j, i*(BMP_GRASSBLOCK_HEIGHT), BMP_GRASSBLOCK_WIDTH, BMP_GRASSBLOCK_HEIGHT, BMP_GRASSBLOCK_DATA);
			}
		}
	}
}

bool isFloor(uint8_t level, uint16_t x, uint16_t y) { 
	if(level > NUM_LEVELS) {
		return false;
		//GLCD_DisplayString(0, 0, 1, "Invalid lvl isFloor!");
		//for(;;); // get stuck here for debugger!
	}

	level--;
	uint16_t floor = y / BMP_GRASSBLOCK_HEIGHT - 1;
	if(floor < 0) floor = 0;
	
	if(left_offset[level][floor] < 0) return false;
	
	uint8_t blocksAwayFromRightWall = x/BMP_GRASSBLOCK_WIDTH + 1;
	
	if(blocksAwayFromRightWall > right_offset[level][floor]) {
		uint8_t blocksAwayFromLeftWall = SC_WIDTH/BMP_GRASSBLOCK_WIDTH - blocksAwayFromRightWall;
		if(blocksAwayFromLeftWall > left_offset[level][floor]) {
			return true;
	}
	}
	// uint8_t blocksAwayFromLeftWall = (x + BMP_GRASSBLOCK_WIDTH/2)/BMP_GRASSBLOCK_WIDTH;
	// if(left_offset[level][floor] <= blocksAwayFromLeftWall - 1
	// 	&& ((SC_WIDTH/BMP_GRASSBLOCK_WIDTH - right_offset[level][floor]) >= blocksAwayFromLeftWall)) {
	// 		return true;
	// }

	return false;	
}

void drawPortals(uint8_t level){
	if (level == 1){
		portal_pairs[0].p1x = L1_portal_0_x;
		portal_pairs[0].p1y = L1_portal_0_y;
		portal_pairs[0].p2x = L1_portal_1_x;
		portal_pairs[0].p2y = L1_portal_1_y;
		portal_pairs[1].p1x = L1_portal_2_x;
		portal_pairs[1].p1y = L1_portal_2_y;
		portal_pairs[1].p2x = L1_portal_3_x;
		portal_pairs[1].p2y = L1_portal_3_y;
		portal_pairs[2].p1x = L1_portal_4_x;
		portal_pairs[2].p1y = L1_portal_4_y;
		portal_pairs[2].p2x = L1_portal_5_x;
		portal_pairs[2].p2y = L1_portal_5_y;
		for (int i = NUM_L1_PORTALS/2; i < NUM_MAX_PORTALS/2; i++){
			portal_pairs[i].p1x = portal_pairs[i].p2x = 1000;
			portal_pairs[i].p1y = portal_pairs[i].p2y = 1000;
		}
	}
	else if (level == 2){
		portal_pairs[0].p1x = L2_portal_0_x;
		portal_pairs[0].p1y = L2_portal_0_y;
		portal_pairs[0].p2x = L2_portal_1_x;
		portal_pairs[0].p2y = L2_portal_1_y;
		portal_pairs[1].p1x = L2_portal_2_x;
		portal_pairs[1].p1y = L2_portal_2_y;
		portal_pairs[1].p2x = L2_portal_3_x;
		portal_pairs[1].p2y = L2_portal_3_y;
		portal_pairs[2].p1x = L2_portal_4_x;
		portal_pairs[2].p1y = L2_portal_4_y;
		portal_pairs[2].p2x = L2_portal_5_x;
		portal_pairs[2].p2y = L2_portal_5_y;
		portal_pairs[3].p1x = L2_portal_6_x;
		portal_pairs[3].p1y = L2_portal_6_y;
		portal_pairs[3].p2x = L2_portal_7_x;
		portal_pairs[3].p2y = L2_portal_7_y;
		for (int i = NUM_L2_PORTALS/2; i < NUM_MAX_PORTALS/2; i++){
			portal_pairs[i].p1x = portal_pairs[i].p2x = 1000;
			portal_pairs[i].p1y = portal_pairs[i].p2y = 1000;
		}
	}
	//put code in here to draw in the portallalalalallassssss
	for (int i = 0; i < NUM_MAX_PORTALS/2; i++){
		if ((portal_pairs[i].p1x != portal_pairs[i].p2x) || 
				(portal_pairs[i].p1y != portal_pairs[i].p2y)){
					GLCD_Bitmap(portal_pairs[i].p1x,portal_pairs[i].p1y,BMP_PORTAL_WIDTH,BMP_PORTAL_HEIGHT,BMP_PORTAL_DATA);
					GLCD_Bitmap(portal_pairs[i].p2x,portal_pairs[i].p2y,BMP_PORTAL_WIDTH,BMP_PORTAL_HEIGHT,BMP_PORTAL_DATA);
				}	
	}
}

void GUI_Reset_Pot(bool died){
	GLCD_Clear(Blue);
	GLCD_DisplayString(16,8,0, " Rotate Pot counter clockwise to cont... ");
	if (died){
		GLCD_DisplayString(18,4,0, " You died, Try Again... or not, I don't mind ");
	}
	bool pot_reset = false;
	while(!pot_reset){
		pot_reset = (pot_val > 4000) ? true:false;
	}
}

void redraw_all(void){
	osMutexAcquire(game_state_id,osWaitForever);
	if (game_state == LEVEL1){
		GLCD_Clear(Blue);
		drawBackground(1);
		drawPortals(1);
	}
	else{
		GLCD_Clear(Blue);
		drawBackground(2);
		drawPortals(2);
	}	
	osMutexRelease(game_state_id);
}
