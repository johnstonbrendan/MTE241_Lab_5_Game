#include "type_declarations.h"
#ifndef _ENEMY_H
#define _ENEMY_H

#define NUM_OF_ENEMIES 3
#define NUM_OF_FRAMES 5
#define ENEMY_HEIGHT 5
#define ENEMY_WIDTH 5

extern const uint8_t ENEMY_BIT[NUM_OF_ENEMIES][NUM_OF_FRAMES][900];

void enemy_init(void);

void enemy_task(void *arg);

extern osMutexId_t enemy_loc_id;

extern uint32_t enemy_time;

#define ENEMY_EXEC_FREQ 30

extern char_info_t enemies[NUM_OF_ENEMIES];//this may need to be a char_info_t

char_pos_t *enemy_in_path(uint32_t start_x, uint32_t end_x, uint32_t y);

char_pos_t enemy_path(uint8_t enemy, uint32_t enemy_time);



#endif
