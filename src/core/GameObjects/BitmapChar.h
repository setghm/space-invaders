#ifndef __BITMAP_CHAR_H__
#define __BITMAP_CHAR_H__

#include <SDL2/SDL.h>
#include "Structs.h"

typedef struct _BitmapChar_ BitmapChar;

struct _BitmapChar_ {
	char character;
	SDL_Texture *texture;
	Vec2 size;
	BitmapChar *next;
};

BitmapChar *BitmapChar_NewFromTextureName(const char *texture_name, char character);
void BitmapChar_Destroy(BitmapChar *bm_char);
void BitmapChar_Draw(BitmapChar *bm_char, SDL_Renderer *renderer, float *x, float *y, float point_size);

float BitmapChar_GetWidth(BitmapChar *bm_char, float point_size);
float BitmapChar_GetHeight(BitmapChar *bm_char, float point_size);

#endif
