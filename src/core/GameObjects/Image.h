#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Structs.h"
#include "GameObject.h"

#define IMAGE(i)	((Image *) i)

typedef struct _Image_ Image;

struct _Image_ {
	GameObject super;

	Vec2 position;
    Point origin;

    SDL_Texture *texture;

    float scale;
	bool visible;
};

Image *Image_New(const char *texture_name);
void Image_Destroy(Image *image);
void Image_Draw(Image *image, SDL_Renderer *renderer);

void Image_SetX(Image *image, float x);
void Image_SetY(Image *image, float y);
void Image_SetPosition(Image *image, float x, float y);
void Image_SetTexture(Image *image, SDL_Texture *texture);
void Image_SetOriginX(Image *image, float x);
void Image_SetOriginY(Image *image, float y);
void Image_SetOrigin(Image *image, float x, float y);
void Image_SetScale(Image *image, float scale);
void Image_SetVisible(Image *image, bool visible);

float Image_GetX(Image *image);
float Image_GetY(Image *image);
SDL_Texture *Image_GetTexture(Image *image);
float Image_GetOriginX(Image *image);
float Image_GetOriginY(Image *image);
float Image_GetScale(Image *image);
bool Image_IsVisible(Image *image);
float Image_GetDisplayWidth(Image *image);
float Image_GetDisplayHeight(Image *image);

#endif
