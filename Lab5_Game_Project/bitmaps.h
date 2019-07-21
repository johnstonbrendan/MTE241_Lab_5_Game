#ifndef _BITMAPS_H
#define _BITMAPS_H
#include <stdint.h>

#define END_X 1000
#define END_Y 1000

#define SC_WIDTH 320
#define SC_HEIGHT 240

#define BMP_COLOR_BORDER (3)
#define BMP_GRASSBLOCK_WIDTH (20)
#define BMP_GRASSBLOCK_HEIGHT (25)
#define BMP_GRASSBLOCK_DATA ((unsigned char*) grassblock)
	
#define BMP_PORTAL_WIDTH (15)
#define BMP_PORTAL_HEIGHT (15)
#define BMP_PORTAL_DATA ((unsigned char*) NULL)

#define ENEMY_WIDTH (20)
#define ENEMY_HEIGHT (20)
#define BMP_ENEMY_DATA ((unsigned char*) bmp_enemy_data)
#define BMP_TGT_ENEMY_DATA ((unsigned char*) bmp_tgt_enemy_data)
#define BMP_ENEMY_HEIGHT (ENEMY_HEIGHT + BMP_COLOR_BORDER)
#define BMP_ENEMY_WIDTH (ENEMY_WIDTH + BMP_COLOR_BORDER)
	
#define PLAYER_WIDTH (25)
#define PLAYER_HEIGHT (25)
#define BMP_PLAYER_DATA ((unsigned char*) bmp_player_data)
#define BMP_PLAYER_HEIGHT (PLAYER_HEIGHT + BMP_COLOR_BORDER)
#define BMP_PLAYER_WIDTH (PLAYER_WIDTH + BMP_COLOR_BORDER)



extern unsigned char *backgroundBitmap;
extern const unsigned char grassblock[20 * 25 * 2 + 1];
extern const unsigned char bmp_enemy_data[23*23*2 + 1];
extern unsigned char *bmp_tgt_enemy_data;
extern unsigned char bmp_player_data[30*30*2 + 1];

void togglePlayerBitmap();
void initializeTargetEnemy();
void initializeBackgroundBitmap(uint8_t w, uint8_t h, uint16_t colour);




//extern const unsigned char enemy_empty_map[10*10*2];

#endif