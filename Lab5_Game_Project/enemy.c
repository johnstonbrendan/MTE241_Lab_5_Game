#include "enemy.h"
#include <stdlib.h>
#include <stdbool.h>
#include <LPC17xx.h>
#include "cmsis_os2.h"
#include "Pot.h"
#include <math.h>
#include "bitmaps.h"

osMutexId_t enemy_loc_id;

int32_t enemy_time;
//const uint8_t ENEMY_BIT[NUM_OF_ENEMIES][NUM_OF_FRAMES][900];
char_info_t* enemies[NUM_OF_ENEMIES];

void enemy_init(void){
	
	enemy_time = 0;//probably need to change this to be the inital position of the POT
	for (int i = 0; i < NUM_OF_ENEMIES; i++){
		enemies[i] = malloc(sizeof(char_info_t));
	}
//	enemies = malloc(sizeof(char_info_t)*NUM_OF_ENEMIES);
	char_pos_t *temp_pos = malloc(sizeof(char_pos_t));
	temp_pos->x = temp_pos->y = 130;
	enemy_loc_id = osMutexNew(NULL);
	for (int i = 0; i <NUM_OF_ENEMIES; i++){
		//*(enemies[i].pos) = enemy_path(i, enemy_time);
		enemies[i]->pos.x = enemy_path(i).x; //this should be changed to the path functions
		enemies[i]->pos.y = enemy_path(i).y;
		enemies[i]->delta.x = enemies[i]->delta.y = 0;
	}
	free(temp_pos);
	
	//enemy_map = {0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x29, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0xe6, 0x28, 0x06, 0x29, 0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29, 0x06, 0x29};
}

void enemy_task(void *arg){
	while(true){
		osMutexAcquire(pot_val_id,osWaitForever);
		enemy_time = (pot_val - 4095/2);
		enemy_time = enemy_time - enemy_time%10; //this will smooth the graphics as time won't change so easily.
		osMutexRelease(pot_val_id);
		osMutexAcquire(enemy_loc_id,osWaitForever);
		for (int i = 0; i < NUM_OF_ENEMIES; i++){
			(enemies[i]->delta).x = enemy_path(i).x - (enemies[i]->pos).x ; //need to change this to add the delta stuff
			(enemies[i]->delta).y = enemy_path(i).y - (enemies[i]->pos).y; //need to change this to add the delta stuff
		}
		osMutexRelease(enemy_loc_id);
		osThreadYield();//make this to delay
	}
}

char_pos_t *enemy_in_path(uint32_t start_x, uint32_t end_x, uint32_t y){

}

char_pos_t enemy_path(uint8_t enemy){
	char_pos_t temp_pos;
	temp_pos.x = temp_pos.y = -1;
	switch (enemy){
	case 0:
//		temp_pos.x = (uint32_t)sin(enemy_time);//probably have to multiply this by some value for display
	temp_pos.x = enemy_time/100 + 100;
	temp_pos.y = 100;//probably need to adjust this for display
		break;
	case 1:
		temp_pos.x = enemy_time/100+30;
		//temp_pos.y = (uint32_t)tan(enemy_time);
		//temp_pos.y = 20*sin(temp_pos.x)+100;
		temp_pos.y = 100;
		break;
	case 2:
		temp_pos.x = (enemy_time/1000)+200;
		temp_pos.y = (enemy_time/100)+100;
		break;
	default:
		return temp_pos;
	}
	return temp_pos;
}