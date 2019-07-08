#include "GLCD.h"
#include "GUI.h"
#include <stdlib.h>
#include <lpc17xx.h>

#define SCORESTODISP 3
#define NAMELENGTH 4
#define TIMESIGFIGS 4

typedef struct {
	char player[4]; //maximum of a 4 character name
	uint8_t time;
}Score_t;

Score_t highscores[SCORESTODISP];

void GUI_Start(void){
	GLCD_Init();
	GLCD_Clear(Blue);
	//no need mutex here because only the GUI tasks will access it
	for(int i = 0; i < SCORESTODISP; i++){
		highscores[i].time = 0;
	}
	GUI_Menu();
}


void GUI_Menu(void){
	GLCD_Clear(Blue);
	
	char* score_line = malloc(sizeof(highscores[0].player));
	//char score_line[NAMELENGTH];
	score_line = (highscores[0].player);
	GLCD_DisplayString(14, 20, 0, "1. ");
	GLCD_DisplayString(14, 20, 0, score_line);	
	GLCD_DisplayString(14, 20, 0, "2. ");
	GLCD_DisplayString(14, 20, 0, "3. ");
	
}



