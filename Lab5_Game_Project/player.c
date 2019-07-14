#include <stdbool.h>
#include <lpc17xx.h>
#include "player.h"
#include "type_declarations.h"
#include "enemy.h"
#include "pushbutton.h"
#include <stdbool.h>
#include "bitmaps.h"

#define LADDER_HEIGHT 30
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

char_info_t* player_info;
osMutexId_t	player_loc_id;

bool ladder_avaliable(){
	bool temp_avaliable = false;
	osMutexAcquire(player_loc_id,osWaitForever);
	//is ladder there???
	osMutexRelease(player_loc_id);
	return temp_avaliable;
}

void player_init(uint16_t initX, uint16_t initY) { 
    player_info = malloc(sizeof(char_info_t));
    player_loc_id = osMutexNew(NULL);
    
    osMutexAcquire(player_loc_id, osWaitForever);
        player_info->pos.x = initX;
        player_info->pos.y = initY;
        player_info->delta.x = 0; 
        player_info->delta.y = 0;
    osMutexRelease(player_loc_id);
} 

void player_task(void* args){ 
	int16_t horizontalMove,verticalMove = 0;

	while(true) {
		//get the joystick values
		

		// do i need to move? 
		verticalMove = 0;
		osMutexAcquire(joy_val_id, osWaitForever);
				horizontalMove = joy_in->right - joy_in->left;
				joy_in->right = 0;
				joy_in->left = 0;
				joy_in->up = 0x1;
				joy_in->down = 0; //maybe make this a function
		osMutexRelease(joy_val_id);
		if(button_pushed) {
			button_pushed = false;
			if (ladder_avaliable()) verticalMove = LADDER_HEIGHT; // call ladder fnc with current position
		}
   
			int16_t *intended_x = malloc(sizeof(int16_t));
			int16_t *intended_y = malloc(sizeof(int16_t));
		osMutexAcquire(player_loc_id, osWaitForever); 
				*intended_x = player_info->pos.x + horizontalMove;
				*intended_y = player_info->pos.y + verticalMove;
		
				legalize(intended_x, intended_y);
		
				player_info->delta.x = *intended_x - player_info->pos.x;
				
				if(verticalMove) {
						player_info->delta.y = *intended_y - player_info->pos.y;
				}
		osMutexRelease(player_loc_id);
		free(intended_x);
		free(intended_y);
		osThreadYield();// maybe make this a delay
		//(osKernelGetSysTimerFreq() / PLAYER_EXEC_FREQ); this was causing major issues
  }
}

void legalize(int16_t* x, int16_t* y) {//may be able to just put this into the loop direclty to save space 

    // NOTE: May have to be less depending on how the bitmap rendering works
	if(*x > SCREEN_WIDTH - PLAYER_WIDTH) { 
        *x = SCREEN_WIDTH - PLAYER_WIDTH;
    } else if(*x < 0) { 
        *x = 0;
    }

    if(*y > SCREEN_HEIGHT) {//need to fix this to include player size
        *y = SCREEN_HEIGHT;
    } else if (*y< 0) { 
        *y = 0;
    }

//    char_pos_t *enemyInPath = enemy_in_path(player_info->pos.x, *x, *y);
//    if(!(enemyInPath -> x == enemyInPath->y == -1)) { 
//        *x = enemyInPath->x;
//        *y = enemyInPath->y;
//    }

        
}
