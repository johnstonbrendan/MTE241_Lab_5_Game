#include <stdbool.h>
#include <lpc17xx.h>
#include "player.h"
#include "type_declarations.h"


void player_init(uint8_t initX, uint8_t initY) { 
    pos = malloc(sizeof(char_pos_t));
    char_pos_id = osMutexNew(NULL);

    osMutexAcquire(char_pos_id, osWaitForever);
        pos->x = initX;
        pos->y = initY;
    osMutexRelease(char_pos_id);
} 

void player_task(void* args){ 
    while(true) {
        // do i need to move? 
        int32_t moveAmount = 0;
        osMutexAcquire(joy_val_id, osWaitForever);
            moveAmount = joy_in->right - joy_in->left;
            joy_in -> right = joy_in -> left = 0;
        osMutexRelease(joy_val_id);

        bool moveUp = button_pushed;
        
        // can i move there?

            // change moveAmount to how much move is allowed, change moveUp to false if going up isn't allowed

        // if i can, move. if not don't

        osMutexAcquire(char_pos_id, osWaitForever);
            if(moveUp) {
                //trigger anim
            }
        osMutexRelease();

        osMutexAcquire(char_pos_id, osWaitForever);
            for(int i = 0; i < abs(moveAmount); i++) {
                pos
            }
        osMutexRelease();
        
        

        osDelay(osKernelGetSysTimerFreq() / PLAYER_EXEC_FREQ);
    }
}