#include <stdint.h>
#include "type_declarations.h" 
#ifndef _PLAYER_H
#define _PLAYER_H

#define PLAYER_EXEC_FREQ 30

void player_init(uint8_t initX, uint8_t initY);

osMutexId_t player_loc_id;
char_pos_t *player_pos;
char_pos_t *player_delta;
void player_task(void* args);
void ensureLegal(int32_t *x, int32_t *y);


#endif