#include <stdbool.h>
#include <lpc17xx.h>
#include "player.h"
#include "type_declarations.h"
#include "enemy.h"
#include "pushbutton.h"
#include <stdbool.h>
#include "bitmaps.h"
#include "GUI.h"

char_info_t* player_info;
osMutexId_t	player_loc_id;

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

void player_reset(void) {
	  osMutexAcquire(player_loc_id, osWaitForever);
				player_info->pos.x = (game_state == LEVEL1) ? PLAYER_L1_INIT_X: PLAYER_L2_INIT_X;
        player_info->pos.y = (game_state == LEVEL1) ? PLAYER_L1_INIT_Y: PLAYER_L2_INIT_Y;
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
				joy_in->up = 0;
				joy_in->down = 0; //maybe make this a function
		osMutexRelease(joy_val_id);
			int16_t *intended_x = malloc(sizeof(int16_t));
			int16_t *intended_y = malloc(sizeof(int16_t));
		osMutexAcquire(player_loc_id, osWaitForever); 
			*intended_x = player_info->pos.x + horizontalMove;
			*intended_y = player_info->pos.y + verticalMove;
	
			legalize(intended_x, intended_y);
			if (horizontalMove && !player_info->teleport)
			{
				player_info->delta.x = *intended_x - player_info->pos.x;
			}
			if(verticalMove && !player_info->teleport) {
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
	if(*x > SC_WIDTH - PLAYER_WIDTH) { 
        *x = SC_WIDTH - PLAYER_WIDTH;
    } else if(*x < 0) { 
        *x = 0;
    }

    if(*y > SC_HEIGHT) {//need to fix this to include player size
        *y = SC_HEIGHT;
    } else if (*y< 0) { 
        *y = 0;
    }

	int16_t temp_x = *x;
	int16_t temp_y = *y;
	while(!isFloor(game_state, temp_x, temp_y) || !isFloor(game_state, temp_x, temp_y)){
		// bring back x one grassblock width towards player
		temp_x = temp_x - (temp_x - player_info->pos.x)/abs(temp_x - player_info->pos.x); // * BMP_GRASSBLOCK_W?
		// we can even add falling like this? maybe?
	}
	
	*x = temp_x;        
}
