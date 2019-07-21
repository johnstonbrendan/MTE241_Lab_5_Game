#include <stdint.h>
#include "type_declarations.h" 
#ifndef _PLAYER_H
#define _PLAYER_H

#define PLAYER_EXEC_FREQ 30
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320
#define PLAYER_L1_INIT_X 216
#define PLAYER_L1_INIT_Y 100

#define PLAYER_L2_INIT_X 160
#define PLAYER_L2_INIT_Y 160


void player_init(uint16_t initX, uint16_t initY);

extern osMutexId_t player_loc_id;
extern char_info_t* player_info;
void player_task(void* args);
void legalize(int16_t* x, int16_t* y);
extern bool portal_avaliable(void);
void player_reset(void);


#endif