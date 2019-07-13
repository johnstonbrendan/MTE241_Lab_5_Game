#include "enemy.h"
#include <stdlib.h>
#include <stdbool.h>
#include <LPC17xx.h>
#include "cmsis_os2.h"
#include "Pot.h"
#include <math.h>



void enemy_init(void){
	enemy_loc_id = osMutexNew(NULL);
	enemies = malloc(sizeof(char_pos_t)*NUM_OF_ENEMIES);
	enemy_time = 0;
	osMutexAcquire(enemy_loc_id)
	for (int i = 0; i <NUM_OF_ENEMIES; i++){
		enemies[i] = enemy_path(i, enemy_time);
		//can't just do this need to have the delta and all that stuff here too'
	}
	osMutexRelease(enemy_loc_id);
}

void enemy_task(void){
	osMutexAcquire(pot_val_id);
	enemy_time = pot_val - 4096/2;
	osMutexRelease(pot_val_id);
	osMutexAcquire(enemy_loc_id);
	for (int i = 0; i < NUM_OF_ENEMIES; i++){
		enemies[i] = enemy_path(i, enemy_time);
	}
	osMutexRelease(enemy_loc_id);
}

char_pos_t enemy_in_path(uint32_t start_x, uint32_t end_x, uint32_t y){

}

char_pos_t enemy_path(uint8_t enemy, uint32_t enemy_time){
	char_pos_t temp_pos;
	temp_pos->x = temp_pos->y = -1;
	switch (enemy){
	case 1:
		temp_pos->x = (uint32_t)sin(enemy_time);//probably have to multiply this by some value for display
		temp_pos->y = 1;//probably need to adjust this for display
		break;
	case 2:
		temp_pos->x = 5;
		temp_pos->y = (uint32_t)tan(enemy_time);
		break;
	case 3:
		temp_pos->x = exp(enemy_time/5);
		temp_pos->y = tanh(enemy_time);
		break;
	}
	return temp_pos
}