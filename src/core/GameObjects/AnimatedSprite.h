#ifndef __ANIMATED_SPRITE_H__
#define __ANIMATED_SPRITE_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Sprite.h"
#include "Animation.h"

#define ANIMATED_SPRITE(as)	((AnimatedSprite *) as)

typedef struct _AnimatedSprite_ AnimatedSprite;

struct _AnimatedSprite_ {
    Sprite super;
    float elapsed_time;
    float last_time;
    bool playing;
    Animation *animation;
    AnimationFrame *current_frame;
};

AnimatedSprite *AnimatedSprite_New();
void AnimatedSprite_Destroy(AnimatedSprite *animated_sprite);
void AnimatedSprite_Draw(AnimatedSprite *animated_sprite, SDL_Renderer *renderer);

void AnimatedSprite_PlayAnimation(AnimatedSprite *animated_sprite);
void AnimatedSprite_PauseAnimation(AnimatedSprite *animated_sprite);
void AnimatedSprite_RestartAnimation(AnimatedSprite *animated_sprite);

void AnimatedSprite_SetAnimation(AnimatedSprite *animated_sprite, Animation *animation);
void AnimatedSprite_SetCurrentFrame(AnimatedSprite *animated_sprite, AnimationFrame *current_frame);

Animation *AnimatedSprite_GetAnimation(AnimatedSprite *animated_sprite);
AnimationFrame *AnimatedSprite_GetCurrentFrame(AnimatedSprite *animated_sprite);

#endif
