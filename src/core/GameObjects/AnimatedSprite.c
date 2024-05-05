#include "AnimatedSprite.h"

#include <stdlib.h>
#include <string.h>

extern void Sprite_SetSize(Sprite *sprite, float w, float h);
extern float Sprite_GetBodyX(Sprite *sprite);
extern float Sprite_GetBodyY(Sprite *sprite);
extern void Sprite_DefaultInit(Sprite *sprite);

AnimatedSprite *AnimatedSprite_New() {
    AnimatedSprite *animated_sprite = (AnimatedSprite *) malloc(sizeof(AnimatedSprite));
    memset(animated_sprite, 0, sizeof(AnimatedSprite));

    Sprite_DefaultInit(SPRITE(animated_sprite));
    AnimatedSprite_PlayAnimation(animated_sprite);

    return animated_sprite;
}

inline void AnimatedSprite_Destroy(AnimatedSprite *animated_sprite) {
    // Release the animation separately
    free(animated_sprite);
}

void AnimatedSprite_Draw(AnimatedSprite *animated_sprite, SDL_Renderer *renderer) {
    if (animated_sprite->animation == NULL)
        return;

    bool playable = !(animated_sprite->animation->_begin == animated_sprite->animation->_end && animated_sprite->animation->frame_count <= 2);

    if (animated_sprite->playing && playable) {
        float current_time = SDL_GetTicks64() / 1000.0f;
        animated_sprite->elapsed_time += current_time - animated_sprite->last_time;
        animated_sprite->last_time = current_time;

        if (animated_sprite->elapsed_time > animated_sprite->animation->duration_per_frame) {
            animated_sprite->elapsed_time = 0;

            if (animated_sprite->current_frame->next == NULL) {
                animated_sprite->current_frame = animated_sprite->animation->_begin;
            } else {
                animated_sprite->current_frame = animated_sprite->current_frame->next;
            }
        }

        Sprite_SetTexture(SPRITE(animated_sprite), animated_sprite->current_frame->data);
    }

    Sprite_Draw(SPRITE(animated_sprite), renderer);
}

inline void AnimatedSprite_PlayAnimation(AnimatedSprite *animated_sprite) {
    animated_sprite->playing = true;
}

inline void AnimatedSprite_PauseAnimation(AnimatedSprite *animated_sprite) {
    animated_sprite->playing = false;
}

inline void AnimatedSprite_RestartAnimation(AnimatedSprite *animated_sprite) {
    animated_sprite->current_frame = animated_sprite->animation->_begin;
    Sprite_SetTexture(SPRITE(animated_sprite), animated_sprite->current_frame->data);
}

void AnimatedSprite_SetAnimation(AnimatedSprite *animated_sprite, Animation *animation) {
    if (animated_sprite->animation == animation) return;

    // Check if this is the first time setting the animation
    bool update_position = (animated_sprite->animation == NULL);

    // Use the animation
    animated_sprite->animation = animation;
    animated_sprite->current_frame = animation->_begin;

    // Set sprite size as the animation size
    Sprite_SetSize(SPRITE(animated_sprite), GameObject_GetWidth(GAME_OBJECT(animation)), GameObject_GetHeight(GAME_OBJECT(animation)));

    // If this is the first time updating the animation then update the position
    // This is usefull if you call Sprite_SetPosition before call this function
    if (update_position) {
        Sprite_SetPosition(SPRITE(animated_sprite), Sprite_GetBodyX(SPRITE(animated_sprite)), Sprite_GetBodyY(SPRITE(animated_sprite)));
    }

    Sprite_SetTexture(SPRITE(animated_sprite), animated_sprite->current_frame->data);
}

// Setters

inline void AnimatedSprite_SetCurrentFrame(AnimatedSprite *animated_sprite, AnimationFrame *current_frame) {
    animated_sprite->current_frame = current_frame;
}

// Getters

Animation *AnimatedSprite_GetAnimation(AnimatedSprite *animated_sprite) {
    return animated_sprite->animation;
}

AnimationFrame *AnimatedSprite_GetCurrentFrame(AnimatedSprite *animated_sprite) {
    return animated_sprite->current_frame;
}
