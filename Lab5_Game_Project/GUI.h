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
#define RESET_POT 5


#define NUM_FLOORS 10

#define NUM_MAX_PORTALS 10 //must be even
#if GOD_MODE
#define NUM_L1_PORTALS 0
#define NUM_L2_PORTALS 0
#else
#define NUM_L1_PORTALS 6
#define NUM_L2_PORTALS 8
#endif

#define L1_portal_0_x 217 //make sure the y1 is smaller than the y2 and check that they are exactly above the level by a portal height value
#define L1_portal_0_y 25
#define L1_portal_1_x 253
#define L1_portal_1_y 100
#define L1_portal_2_x 0
#define L1_portal_2_y 25
#define L1_portal_3_x 291
#define L1_portal_3_y 175
#define L1_portal_4_x 70
#define L1_portal_4_y 100
#define L1_portal_5_x 120
#define L1_portal_5_y 175

#define L2_portal_0_x 145 //make sure the y1 is smaller than the y2 and check that they are exactly above the level by a portal height value
#define L2_portal_0_y 100
#define L2_portal_1_x 160
#define L2_portal_1_y 200
#define L2_portal_2_x 232
#define L2_portal_2_y 25
#define L2_portal_3_x 145
#define L2_portal_3_y 25
#define L2_portal_4_x 295
#define L2_portal_4_y 25
#define L2_portal_5_x 295
#define L2_portal_5_y 200
#define L2_portal_6_x 170
#define L2_portal_6_y 25
#define L2_portal_7_x 45
#define L2_portal_7_y 100

void GUI_Start(void);

void GUI_Task(void * arg);

void GUI_Level_Menu(void);

void GUI_Level_1(void);

void GUI_Level_2(void);

void animate_enemy(char_info_t *enemy, bool to_catch);

void animate_player(void);

void animate_collisions(void);

void animate_portals(void);

void drawBackground(uint8_t level);

bool isFloor(uint8_t level, uint16_t x, uint16_t y);

void drawPortals(uint8_t level);

bool check_collision(uint16_t object_1_x, uint16_t object_1_y, uint16_t object_2_x, uint16_t object_2_y, 
						uint8_t object_1_h, uint8_t object_1_w, uint8_t object_2_h, uint8_t object_2_w);

void redraw_all(void);

void GUI_Reset_Pot(bool died);

#endif
