#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void TextureManager_Init(SDL_Renderer *_renderer);
void TextureManager_Load(const char *name, const char *filename);
SDL_Texture *TextureManager_Get(const char *name, SDL_Rect *rect_copy_dest);
void TextureManager_Clean();

#endif
