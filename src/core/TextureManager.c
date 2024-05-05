#include "TextureManager.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <Config.h>

struct _MemoryTexture_ {
    char *name;
    SDL_Texture *data;
    SDL_Rect rect_src;
    struct _MemoryTexture_ *next;
};

struct _LoadedTextures_ {
    int count;
    struct _MemoryTexture_ *begin;
    struct _MemoryTexture_ *end;
} LoadedTextures;

SDL_Renderer *renderer;

void TextureManager_Init(SDL_Renderer *_renderer) {
    int init_formats = IMG_INIT_PNG;
    IMG_Init(init_formats);

    LoadedTextures.count = 0;
    LoadedTextures.begin = NULL;
    LoadedTextures.end = NULL;

    renderer = _renderer;
}

void TextureManager_Load(const char *name, const char *filename) {
    // Prepend the filename with the assets directory
    char *fpath = (char *) malloc(strlen(filename) + strlen(ASSETS_DIRECTORY) + 1);
    sprintf(fpath, "%s%s\0", ASSETS_DIRECTORY, filename);

#ifdef DEBUG
    fprintf(stderr, "LOG: loading %s (%s)...", fpath, name);
#endif

	// Check if the file exists
    if (access(fpath, F_OK) != 0) {
#ifdef DEBUG
        fprintf(stderr, "\tERROR the file doesn't exists\n");
#endif
        return;
    }

    // Create a new texture
    struct _MemoryTexture_ *mem = (struct _MemoryTexture_ *) malloc(sizeof(struct _MemoryTexture_));
    memset(mem, 0, sizeof(struct _MemoryTexture_));

    SDL_Surface *surface = IMG_Load(fpath);

    mem->rect_src.x = 0;
    mem->rect_src.y = 0;
    mem->rect_src.w = surface->w;
    mem->rect_src.h = surface->h;

    mem->data = SDL_CreateTextureFromSurface(renderer, surface);
    mem->name = strdup(name);
    mem->next = NULL;

    SDL_FreeSurface(surface);

    // Add to the loaded textures
    if (LoadedTextures.begin == NULL) {
        LoadedTextures.begin = mem;
    }

    if (LoadedTextures.end != NULL) {
        LoadedTextures.end->next = mem;
    }

    LoadedTextures.end = mem;
    LoadedTextures.count++;

#ifdef DEBUG
    fprintf(stderr, "\tLOADED! (name: \"%s\")\n", name);
#endif
}

SDL_Texture *TextureManager_Get(const char *name, SDL_Rect *rect_copy_dest) {
    struct _MemoryTexture_ *mem = LoadedTextures.begin;

    while (mem != NULL) {
        if (strcmp(name, mem->name) == 0) {

            if (rect_copy_dest != NULL) {
                rect_copy_dest->x = mem->rect_src.x;
                rect_copy_dest->y = mem->rect_src.y;
                rect_copy_dest->w = mem->rect_src.w;
                rect_copy_dest->h = mem->rect_src.h;
            }

            return mem->data;
        }
        mem = mem->next;
    }

    return NULL;
}

void TextureManager_Clean() {
    struct _MemoryTexture_ *curr = LoadedTextures.begin;
    struct _MemoryTexture_ *next = NULL;

    while (curr != NULL) {
        next = curr->next;

        if (curr->name != NULL) {
            free(curr->name);
        }
        if (curr->data != NULL) {
            SDL_DestroyTexture(curr->data);
        }

        LoadedTextures.count--;
        curr = next;
    }

    LoadedTextures.begin = NULL;
    LoadedTextures.end = NULL;

    IMG_Quit();
}
