#include "BitmapText.h"

#include <stdlib.h>
#include <string.h>

#include <Config.h>

extern void GameObject_SetSize(GameObject *object, float width, float height);
extern void BitmapFont_DrawText(BitmapFont *bm_font, SDL_Renderer *renderer, const char *text, float x, float y, float point_size);

// Private
void BitmapText_DefaultInit(BitmapText *bm_text) {
	BitmapText_SetPointSize(bm_text, BITMAP_TEXT_DEFAULT_POINT_SIZE);
	BitmapText_SetVisible(bm_text, true);
}

// Private
void BitmapText_SetSize(BitmapText *bm_text, float width, float height) {
	GameObject_SetSize(GAME_OBJECT(bm_text), width, height);
}

// Private
void BitmapText_CalculateSize(BitmapText *bm_text) {
	float width = 0;
	int len = strlen(bm_text->text);

	for (int i=0; i<len; i++) {
		width += BitmapFont_GetCharWidth(bm_text->font, bm_text->text[i], bm_text->point_size);
	}

	BitmapText_SetSize(bm_text, width, bm_text->point_size);
}

BitmapText *BitmapText_New(BitmapFont *font, const char *text) {
	BitmapText *bm_text = (BitmapText *) malloc(sizeof(BitmapText));
	memset(bm_text, 0, sizeof(BitmapText));

	bm_text->font = font;
	bm_text->text = strdup(text);
	BitmapText_DefaultInit(bm_text);

	return bm_text;
}

void BitmapText_Draw(BitmapText *bm_text, SDL_Renderer *renderer) {
	// Don't draw if the text is not visible
	if (!BitmapText_IsVisible(bm_text))
		return;

	BitmapFont_DrawText(bm_text->font, renderer, bm_text->text, bm_text->position.x, bm_text->position.y, bm_text->point_size);
}

inline void BitmapText_Destroy(BitmapText *bm_text) {
	// Destroy the bitmap font for separately
	if (bm_text) {
		free(bm_text->text);
		bm_text->text = NULL;
	}
	free(bm_text);
}

// Setters

inline void BitmapText_SetPosition(BitmapText *bm_text, float x, float y) {
	BitmapText_SetX(bm_text, x);
	BitmapText_SetY(bm_text, y);
}

inline void BitmapText_SetX(BitmapText *bm_text, float x) {
	bm_text->position.x = x;
}

inline void BitmapText_SetY(BitmapText *bm_text, float y) {
	bm_text->position.y = y;
}

void BitmapText_SetText(BitmapText *bm_text, const char *text) {
	if (bm_text->text != NULL) {
		free(bm_text->text);
	}

	bm_text->text = strdup(text);

	BitmapText_CalculateSize(bm_text);
}

inline void BitmapText_SetFont(BitmapText *bm_text, BitmapFont *font) {
	bm_text->font = font;
}

void BitmapText_SetPointSize(BitmapText *bm_text, float point_size) {
	bm_text->point_size = point_size;
	BitmapText_CalculateSize(bm_text);
}

inline void BitmapText_SetVisible(BitmapText *bm_text, bool show) {
	bm_text->visible = show;
}

// Getters

inline float BitmapText_GetX(BitmapText *bm_text) {
	return bm_text->position.x;
}

inline float BitmapText_GetY(BitmapText *bm_text) {
	return bm_text->position.y;
}

inline const char *BitmapText_GetText(BitmapText *bm_text) {
	return (const char*) bm_text->text;
}

inline BitmapFont *BitmapText_GetFont(BitmapText *bm_text) {
	return bm_text->font;
}

inline float BitmapText_GetPointSize(BitmapText *bm_text) {
	return bm_text->point_size;
}

inline unsigned int BitmapText_GetLength(BitmapText *bm_text) {
	return bm_text->length;
}

inline bool BitmapText_IsVisible(BitmapText *bm_text) {
	return bm_text->visible;
}

float BitmapText_GetDisplayWidth(BitmapText *bm_text) {
	return GameObject_GetWidth(GAME_OBJECT(bm_text)) * POINTS_IN_PIXELS;
}

float BitmapText_GetDisplayHeight(BitmapText *bm_text) {
	return GameObject_GetHeight(GAME_OBJECT(bm_text)) * POINTS_IN_PIXELS;
}
