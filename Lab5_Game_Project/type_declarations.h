/* Use this file to keep all of the structs and the mutex ids */

#include <stdlib.h>
#include <lpc17xx.h>
#include "cmsis_os2.h"
#include <stdbool.h>

#ifndef _TYPE_DECL_H
#define _TYPE_DECL_H
typedef struct{
	uint8_t up;
	uint8_t down;
	uint8_t left;
	uint8_t right;
}joy_count_t;

typedef struct{
	int16_t x;
	int16_t y;
}char_pos_t;

typedef struct {
	char_pos_t pos;
	char_pos_t delta;
	bool teleport;
} char_info_t;

typedef struct{// p1 always at lower y value
	int16_t p1x;
	int16_t p1y;
	int16_t p2x;
	int16_t p2y;
}portal_pair_t;

extern uint8_t game_state;
extern joy_count_t* joy_in;
extern uint32_t pot_val;
	
extern osMutexId_t joy_val_id;
extern osMutexId_t pot_val_id;
extern osMutexId_t game_state_id;
extern osMutexId_t player_loc_id;
extern osMutexId_t enemy_loc_id;



#endif