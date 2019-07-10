#include <stdlib.h>
#include <lpc17xx.h>

#ifndef _TYPE_DECL_H
#define _TYPE_DECL_H
typedef struct{
	uint8_t up;
	uint8_t down;
	uint8_t left;
	uint8_t right;
}pot_count_t;

typedef struct{
	uint8_t x;
	uint8_t y;
}char_pos_t;

extern uint8_t game_state;
#endif