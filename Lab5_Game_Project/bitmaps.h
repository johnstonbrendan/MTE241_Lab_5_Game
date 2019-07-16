#ifndef _BITMAPS_H
#define _BITMAPS_H

#define SC_WIDTH 320
#define SC_HEIGHT 240

#define BMP_GRASSBLOCK_WIDTH (20)
#define BMP_GRASSBLOCK_HEIGHT (25)
#define BMP_GRASSBLOCK_DATA ((unsigned char*) grassblock)

#define ENEMY_WIDTH (30)
#define ENEMY_HEIGHT (30)
#define BMP_ENEMY_DATA ((unsigned char*) enemy)
	
#define PLAYER_WIDTH (30)
#define PLAYER_HEIGHT (30)

extern const unsigned char grassblock[20 * 25 * 2 + 1];
extern const unsigned char enemy[30*30*2 + 1];

//extern const unsigned char enemy_empty_map[10*10*2];

#endif