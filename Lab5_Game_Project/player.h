#include <stdint.h>
#include "type_declarations.h" 
#ifndef _PLAYER_H
#define _PLAYER_H

#define PLAYER_EXEC_FREQ 30
#define LADDER_HEIGHT 30
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320
#define PLAYER_INIT_X 150
#define PLAYER_INIT_Y 70

void player_init(uint16_t initX, uint16_t initY);

extern osMutexId_t player_loc_id;
extern char_info_t* player_info;
void player_task(void* args);
void legalize(int16_t* x, int16_t* y);
extern bool ladder_avaliable(void);


#endif