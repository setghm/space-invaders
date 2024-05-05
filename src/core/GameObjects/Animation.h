#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>
#include <stdarg.h>
#include "GameObject.h"

#define ANIMATION(a)    ((Animation *) a)

typedef struct _Animation_ Animation;
typedef struct _AnimationFrame_ AnimationFrame;

struct _Animation_ {
    GameObject super;
    int frame_count;
    float duration_per_frame;
    AnimationFrame *_begin;
    AnimationFrame *_end;
};

struct _AnimationFrame_ {
    SDL_Texture *data;
    AnimationFrame *next;
};

// Animation
Animation *Animation_New(int frame_count, ...);
void Animation_Destroy(Animation *animation);

void Animation_SetDurationPerFrame(Animation *animation, float value);

float Animation_GetDurationPerFrame(Animation *animation);
float Animation_GetDuration(Animation *animation);

#endif
