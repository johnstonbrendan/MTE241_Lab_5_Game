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

#define NUM_MAX_PORTALS 6 //must be even
#define NUM_L1_PORTALS 4
#define NUM_L2_PORTALS 6

#define L1_portal_0_x 100 //make sure the y1 is larger than the y2 and check that they are exactly above the level by a portal height value
#define L1_portal_0_y 150
#define L1_portal_1_x 50
#define L1_portal_1_y 200
#define L1_portal_2_x 100
#define L1_portal_2_y 0
#define L1_portal_3_x 200
#define L1_portal_3_y 70

#define L2_portal_0_x 0 //make sure the y1 is larger than the y2 and check that they are exactly above the level by a portal height value
#define L2_portal_0_y 50
#define L2_portal_1_x 50
#define L2_portal_1_y 100
#define L2_portal_2_x 100
#define L2_portal_2_y 0
#define L2_portal_3_x 200
#define L2_portal_3_y 70
#define L2_portal_4_x 38
#define L2_portal_4_y 70
#define L2_portal_5_x 150
#define L2_portal_5_y 100

void GUI_Start(void);

void GUI_Task(void * arg);

void GUI_Level_Menu(void);

void GUI_Level_1(void);

void animate_enemy(char_info_t *enemy);

void animate_player(void);

void animate_collisions(void);

void animate_portals(void);

void drawBackground(uint8_t level);

bool isFloor(uint8_t level, uint16_t x, uint16_t y);

void drawPortals(uint8_t level);

bool check_collision(uint16_t player_x, uint16_t player_y, uint16_t object_x, uint16_t object_y, uint8_t object_h, uint8_t object_w);


#endif
