#include "Image.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <Config.h>
#include <TextureManager.h>

// Private
void Image_DefaultInit(Image *image) {
	Image_SetOrigin(image, DEFAULT_ORIGIN_X, DEFAULT_ORIGIN_Y);
    Image_SetScale(image, IMAGE_DEFAULT_SCALE);
    Image_SetVisible(image, IMAGE_DEFAULT_VISIBILITY);
}

// Private
void Image_SetSize(Image *image, float w, float h) {
    GameObject_SetSize(GAME_OBJECT(image), w, h);
}

Image *Image_New(const char *texture_name) {
	Image *image = (Image *) malloc(sizeof(Image));
	memset(image, 0, sizeof(Image));

	SDL_Rect rect;

    Image_SetTexture(image, TextureManager_Get(texture_name, &rect));
    Image_SetSize(image, rect.w, rect.h);
	Image_DefaultInit(image);

#ifdef DEBUG
	if (image->texture == NULL) {
        fprintf(stderr, "ERROR: Texture \"%s\" is not loaded\n", texture_name);
    }
#endif

	return image;
}

inline void Image_Destroy(Image *image) {
	// The Texture Manager will free all the loaded textures
	free(image);
}

void Image_Draw(Image *image, SDL_Renderer *renderer) {
    // Don't draw if the image is not visible
    if (!image->visible) return;

    // Apply scale and pivot offset (origin)
    SDL_Rect transformations = {
        (int) roundf(Image_GetX(image)),
        (int) roundf(Image_GetY(image)),
        (int) roundf(Image_GetDisplayWidth(image)),
        (int) roundf(Image_GetDisplayHeight(image))
    };

    SDL_RenderCopy(renderer, image->texture, NULL, &transformations);
}

// Setters

inline void Image_SetX(Image *image, float x) {
	image->position.x = x;
}

inline void Image_SetY(Image *image, float y) {
	image->position.y = y;
}

inline void Image_SetPosition(Image *image, float x, float y) {
	image->position.x = x;
	image->position.y = y;
}

inline void Image_SetTexture(Image *image, SDL_Texture *texture) {
	image->texture = texture;
}

inline void Image_SetOriginX(Image *image, float x) {
	image->origin.x = x;
}

inline void Image_SetOriginY(Image *image, float y) {
	image->origin.y = y;
}

inline void Image_SetOrigin(Image *image, float x, float y) {
	image->origin.x = x;
	image->origin.y = y;
}

inline void Image_SetScale(Image *image, float scale) {
	// Calculate the engine scale
	image->scale = scale * DEFAULT_SCALE;
}

inline void Image_SetVisible(Image *image, bool visible) {
	image->visible = visible;
}

// Getters

inline float Image_GetX(Image *image) {
	return image->position.x - Image_GetDisplayWidth(image) * image->origin.x;
}

inline float Image_GetY(Image *image) {
	return image->position.y - Image_GetDisplayHeight(image) * image->origin.y;
}

inline SDL_Texture *Image_GetTexture(Image *image) {
	return image->texture;
}

inline float Image_GetOriginX(Image *image) {
	return image->origin.x;
}

inline float Image_GetOriginY(Image *image) {
	return image->origin.y;
}

inline float Image_GetScale(Image *image) {
	// Get the original scale
	return image->scale / DEFAULT_SCALE;
}

inline bool Image_IsVisible(Image *image) {
	return image->visible;
}

inline float Image_GetDisplayWidth(Image *image) {
	return GameObject_GetWidth(GAME_OBJECT(image)) * image->scale;
}

inline float Image_GetDisplayHeight(Image *image) {
	return GameObject_GetHeight(GAME_OBJECT(image)) * image->scale;
}
