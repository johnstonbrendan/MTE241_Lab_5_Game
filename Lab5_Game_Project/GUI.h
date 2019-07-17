#include "type_declarations.h"

#ifndef _GUI_H
#define _GUI_H

// Level Definitions
#define NUM_LEVELS 2
#define MAINMENU 0
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL1_COMPLETE 3
#define LEVEL2_COMPLETE 4


#define NUM_FLOORS 10

void GUI_Start(void);

void GUI_Task(void * arg);

void GUI_Level_Menu(void);

void GUI_Level_1(void);

void animate_enemy(char_info_t *enemy);

void animate_player(void);

void animate_collisions(void);

uint16_t dist_between_points(uint16_t player_x, uint16_t player_y, uint16_t enemy_x, uint16_t enemy_y);

void drawBackground(uint8_t level);

bool isFloor(uint8_t level, uint16_t x, uint16_t y);

#endif
