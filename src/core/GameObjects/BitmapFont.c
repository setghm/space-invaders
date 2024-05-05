#include "BitmapFont.h"

#include <stdlib.h>
#include <string.h>

#include <Config.h>
#include "BitmapChar.h"

BitmapFont *BitmapFont_New() {
	BitmapFont *bm_font = (BitmapFont *) malloc(sizeof(BitmapFont));
	memset(bm_font, 0, sizeof(BitmapFont));
	return bm_font;
}

void BitmapFont_AddCharacter(BitmapFont *bm_font, const char *texture_name, char character) {
	BitmapChar *bm_char = BitmapChar_NewFromTextureName(texture_name, character);

	if (bm_font->first == NULL) {
		bm_font->first = bm_char;
	}

	if (bm_font->last != NULL) {
		bm_font->last->next = bm_char;
	}

	bm_font->last = bm_char;
	bm_font->count++;
}

void BitmapFont_Destroy(BitmapFont *bm_font) {
	// Remove one by one each character
	BitmapChar *bm_char = bm_font->first;
	BitmapChar *bm_next;

	while (bm_char) {
		bm_next = bm_char->next;
		BitmapChar_Destroy(bm_char);
		bm_char = bm_next;
	}

	// Remove the structure itself
	free(bm_font);
}

// Private
BitmapChar *BitmapFont_GetChar(BitmapFont *bm_font, char c) {
	BitmapChar *bm_char = bm_font->first;

	while (bm_char) {
		if (bm_char->character == c) {
			return bm_char;
		}
		bm_char = bm_char->next;
	}

	return NULL;
}

// Private
void BitmapFont_DrawChar(BitmapFont *bm_font, SDL_Renderer *renderer, char c, float *x, float *y, float point_size) {
	BitmapChar *bm_char = BitmapFont_GetChar(bm_font, c);

	if (bm_char) {
		BitmapChar_Draw(bm_char, renderer, x, y, point_size);
	}
}

// Private
void BitmapFont_DrawText(BitmapFont *bm_font, SDL_Renderer *renderer, const char *text, float x, float y, float point_size) {
	int len = strlen(text);

	for (int i=0; i<len; i++) {
		if (text[i] == ' ') {
			x += FONT_WHITESPACE_WIDTH(point_size);
		} else {
			BitmapFont_DrawChar(bm_font, renderer, text[i], &x, &y, point_size);
		}
	}
}

float BitmapFont_GetCharWidth(BitmapFont *bm_font, char c, float point_size) {
	BitmapChar *bm_char = BitmapFont_GetChar(bm_font, c);

	if (bm_char) {
		return BitmapChar_GetWidth(bm_char, point_size) + FONT_CHAR_SPACING(point_size);
	}

	return 0;
}

float BitmapFont_GetCharHeight(BitmapFont *bm_font, char c, float point_size) {
	BitmapChar *bm_char = BitmapFont_GetChar(bm_font, c);

	if (bm_char) {
		return BitmapChar_GetHeight(bm_char, point_size);
	}

	return 0;
}
