#include "BitmapChar.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <TextureManager.h>
#include <Config.h>

BitmapChar *BitmapChar_NewFromTextureName(const char *texture_name, char character) {
	BitmapChar *bm_char = (BitmapChar *) malloc(sizeof(BitmapChar));
	memset(bm_char, 0, sizeof(BitmapChar));

	bm_char->character = character;

	SDL_Rect rect;
    bm_char->texture = TextureManager_Get(texture_name, &rect);
	bm_char->size.x = rect.w;
	bm_char->size.y = rect.h;

#ifdef DEBUG
    if (bm_char->texture == NULL) {
        fprintf(stderr, "ERROR: Texture \"%s\" is not loaded\n", texture_name);
    }
#endif

	return bm_char;
}

void BitmapChar_Destroy(BitmapChar *bm_char) {
	// The Texture Manager will free all the loaded textures
	free(bm_char);
}

void BitmapChar_Draw(BitmapChar *bm_char, SDL_Renderer *renderer, float *x, float *y, float point_size) {
	// Calculate the bitmap character width
	float width = BitmapChar_GetWidth(bm_char, point_size);
	float height = BitmapChar_GetHeight(bm_char, point_size);

	// Apply the transformations
	SDL_Rect transformations = {
		(int) roundf(*x),
		(int) roundf(*y),
		(int) roundf(width * POINTS_IN_PIXELS),
		(int) roundf(height * POINTS_IN_PIXELS)
	};

	// Sum the width of the character for the next character position in the x-axis
	*x += width + FONT_CHAR_SPACING(point_size);

	// Draw the texture
	SDL_RenderCopy(renderer, bm_char->texture, NULL, &transformations);
}

inline float BitmapChar_GetWidth(BitmapChar *bm_char, float point_size) {
	// Get the char width with the rule of 3
	return point_size * bm_char->size.x / bm_char->size.y;
}

inline float BitmapChar_GetHeight(BitmapChar *bm_char, float point_size) {
	return point_size;
}
