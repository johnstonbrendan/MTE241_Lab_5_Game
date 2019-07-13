#include <stdbool.h>
#include <lpc17xx.h>
#include "player.h"
#include "type_declarations.h"
#include "enemy.h"

#define LADDER_HEIGHT 30


void player_init(uint8_t initX, uint8_t initY) { 
    player_pos = malloc(sizeof(char_pos_t));
    player_delta = malloc(sizeof(char_pos_t));
    player_loc_id = osMutexNew(NULL);
    
    osMutexAcquire(player_loc_id, osWaitForever);
        player_pos->x = initX;
        player_pos->y = initY;
        player_delta->x = 0; 
        player_delta->y = 0;
    osMutexRelease(player_loc_id);
} 

void player_task(void* args){ 
	int32_t horizontalMove,verticalMove = 0;

	while(true) {
        // do i need to move? 
        horizontalMove = 0;
        osMutexAcquire(joy_val_id, osWaitForever);
            horizontalMove = joy_in->right - joy_in->left;
            joy_in->right = joy_in->left = 0;
        osMutexRelease(joy_val_id);
        
        verticalMove = 0;

        if(button_pushed) {
            verticalMove = LADDER_HEIGHT; // call ladder fnc with current position
        }

        osMutexAcquire(player_loc_id, osWaitForever);    
            int32_t intended_x = player_pos->x + player_delta->x + horizontalMove;
            int32_t intended_y = player_pos->y + player_delta->y + verticalMove;

            ensureLegal(intended_x, intended_y);
            
            player_delta->x = intended_y - player_pos->y;

            if(verticalMove) {
                player_delta->y = intended_y - player_pos->y;
            }
        osMutexRelease(player_loc_id);

        
        osDelay(osKernelGetSysTimerFreq() / PLAYER_EXEC_FREQ);
    }
}

void ensureLegal(uint32_t &x, uint32_t &y) { 

    // NOTE: May have to be less depending on how the bitmap rendering works
    if(x > SCREEN_WIDTH) { 
        x = SCREEN_WIDTH;
    } else if(x < 0) { 
        x = 0;
    }

    if(y > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT;
    } else if (y < 0) { 
        y = 0;
    }

    char_pos_t enemyInPath = enemy_in_path(player_pos->x, x, y);
    if(!(enemyInPath -> x == enemyInPath->y == -1)) { 
        x = enemyInPath->x;
        y = enemyInPath->y;
    }
        
}
