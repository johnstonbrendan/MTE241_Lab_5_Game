#include <stdint.h>
#include "type_declarations.h" 
#ifndef _PLAYER_H
#define _PLAYER_H

const uint32_t PLAYER_EXEC_FREQ = 30;
const uint8_t PLAYER_NUM_BITMAPS = 10;


osMutexId_t char_pos_id;
char_pos_t *pos;
char_pos_t *need_to_go;
void player_task(void* args);


#endif