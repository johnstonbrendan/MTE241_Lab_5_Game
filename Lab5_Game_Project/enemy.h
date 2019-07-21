#include "type_declarations.h"
#ifndef _ENEMY_H
#define _ENEMY_H

#define MAX_NUM_OF_ENEMIES 7

#if GOD_MODE
#define NUM_OF_L1_ENEMIES 1
#define NUM_OF_L2_ENEMIES 1
#else
#define NUM_OF_L1_ENEMIES 3
#define NUM_OF_L2_ENEMIES 7

#endif


void enemy_init(void);

void enemy_task(void *arg);

extern osMutexId_t enemy_loc_id;

extern int32_t enemy_time;

#define ENEMY_EXEC_FREQ 30

extern char_info_t *enemies[MAX_NUM_OF_ENEMIES];//this may need to be a char_info_t

//extern char_info_t *enemies;//this may need to be a char_info_t

char_pos_t *enemy_in_path(uint32_t start_x, uint32_t end_x, uint32_t y);

char_pos_t enemy_path(uint8_t enemy);



#endif
