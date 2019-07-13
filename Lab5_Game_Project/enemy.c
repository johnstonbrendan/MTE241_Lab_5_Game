#include "enemy.h"
#include <stdlib.h>
#include <stdbool.h>
#include <LPC17xx.h>
#include "cmsis_os2.h"
#include "Pot.h"
#include <math.h>

osMutexId_t enemy_loc_id;

uint32_t enemy_time;
//const uint8_t ENEMY_BIT[NUM_OF_ENEMIES][NUM_OF_FRAMES][900];
char_info_t enemies[NUM_OF_ENEMIES];

void enemy_init(void){
	enemy_time = 0;
	osMutexAcquire(enemy_loc_id,osWaitForever);
	for (int i = 0; i <NUM_OF_ENEMIES; i++){
		*(enemies[i].pos) = enemy_path(i, enemy_time);
		//can't just do this need to have the delta and all that stuff here too'
	}
	osMutexRelease(enemy_loc_id);
}

void enemy_task(void *arg){
	osMutexAcquire(pot_val_id,osWaitForever);
	enemy_time = pot_val - 4096/2;
	osMutexRelease(pot_val_id);
	osMutexAcquire(enemy_loc_id,osWaitForever);
	for (int i = 0; i < NUM_OF_ENEMIES; i++){
		(enemies[i].delta)->x = (enemies[i].pos)->x - enemy_path(i, enemy_time).x; //need to change this to add the delta stuff
		(enemies[i].delta)->y = (enemies[i].pos)->y - enemy_path(i, enemy_time).y; //need to change this to add the delta stuff
	}
	osMutexRelease(enemy_loc_id);
}

char_pos_t *enemy_in_path(uint32_t start_x, uint32_t end_x, uint32_t y){

}

char_pos_t enemy_path(uint8_t enemy, uint32_t enemy_time){
	char_pos_t temp_pos;
	temp_pos.x = temp_pos.y = -1;
	switch (enemy){
	case 1:
		temp_pos.x = (uint32_t)sin(enemy_time);//probably have to multiply this by some value for display
		temp_pos.y = 1;//probably need to adjust this for display
		break;
	case 2:
		temp_pos.x = 5;
		temp_pos.y = (uint32_t)tan(enemy_time);
		break;
	case 3:
		temp_pos.x = exp(enemy_time/5);
		temp_pos.y = tanh(enemy_time);
		break;
	}
	return temp_pos;
}