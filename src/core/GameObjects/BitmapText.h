#ifndef __BITMAP_TEXT_H__
#define __BITMAP_TEXT_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Structs.h"
#include "GameObject.h"
#include "BitmapFont.h"

typedef struct _BitmapText_ BitmapText;

struct _BitmapText_ {
	GameObject super;

	BitmapFont *font;			// rw
	char *text;					// rw

	float point_size;			// rw
	unsigned int length;		// r

	Vec2 position;				// rw
	bool visible;				// rw
};

BitmapText *BitmapText_New(BitmapFont *font, const char *text);
void BitmapText_Draw(BitmapText *bm_text, SDL_Renderer *renderer);
void BitmapText_Destroy(BitmapText *bm_text);

void BitmapText_SetPosition(BitmapText *bm_text, float x, float y);
void BitmapText_SetX(BitmapText *bm_text, float x);
void BitmapText_SetY(BitmapText *bm_text, float y);
void BitmapText_SetText(BitmapText *bm_text, const char *text);
void BitmapText_SetFont(BitmapText *bm_text, BitmapFont *font);
void BitmapText_SetPointSize(BitmapText *bm_text, float point_size);
void BitmapText_SetVisible(BitmapText *bm_text, bool show);

float BitmapText_GetX(BitmapText *bm_text);
float BitmapText_GetY(BitmapText *bm_text);
const char *BitmapText_GetText(BitmapText *bm_text);
BitmapFont *BitmapText_GetFont(BitmapText *bm_text);
float BitmapText_GetPointSize(BitmapText *bm_text);
unsigned int BitmapText_GetLength(BitmapText *bm_text);
bool BitmapText_IsVisible(BitmapText *bm_text);
float BitmapText_GetDisplayWidth(BitmapText *bm_text);
float BitmapText_GetDisplayHeight(BitmapText *bm_text);

#endif
