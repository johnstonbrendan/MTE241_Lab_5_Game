#include "type_declarations.h"

#ifndef _GUI_H
#define _GUI_H
void GUI_Start(void);

void GUI_Task(void * arg);

void GUI_Level_Menu(void);

void GUI_Level_1(void);

void animate_enemy(char_info_t *enemy);

void animate_char(char_info_t player);

#endif
