#ifndef __BITMAP_FONT_H__
#define __BITMAP_FONT_H__

#include <SDL2/SDL.h>
#include "Structs.h"
#include "BitmapChar.h"

typedef struct _BitmapFont_ BitmapFont;

struct _BitmapFont_ {
	unsigned int count;
	BitmapChar *first;
	BitmapChar *last;
};

BitmapFont *BitmapFont_New();
void BitmapFont_AddCharacter(BitmapFont *bm_font, const char *texture_name, char character);
void BitmapFont_Destroy(BitmapFont *bm_font);

float BitmapFont_GetCharWidth(BitmapFont *bm_font, char c, float point_size);
float BitmapFont_GetCharHeight(BitmapFont *bm_font, char c, float point_size);

#endif
