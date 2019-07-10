/* Use this file to keep all of the structs and the mutex ids */

#include <stdlib.h>
#include <lpc17xx.h>
#include "cmsis_os2.h"

#ifndef _TYPE_DECL_H
#define _TYPE_DECL_H
typedef struct{
	uint8_t up;
	uint8_t down;
	uint8_t left;
	uint8_t right;
}joy_count_t;

typedef struct{
	uint8_t x;
	uint8_t y;
}char_pos_t;


extern uint8_t game_state;
extern joy_count_t* joy_in;
extern uint32_t pot_val;
	
extern osMutexId_t joy_val_id;

extern osMutexId_t pot_val_id;


extern osMutexId_t game_state_id;



#endif