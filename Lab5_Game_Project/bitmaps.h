#ifndef _BITMAPS_H
#define _BITMAPS_H

//extern const unsigned char background_map[320*240*2];


#define ENEMY_WIDTH (30)
#define ENEMY_HEIGHT (30)
#define GIMP_IMAGE_BYTES_PER_PIXEL (2) /* 2:RGB16, 3:RGB, 4:RGBA */
#define GIMP_IMAGE_PIXEL_DATA ((unsigned char*) GIMP_IMAGE_pixel_data)

extern const unsigned char enemy_map[30*30*2 + 1];

//extern const unsigned char enemy_empty_map[10*10*2];

#endif