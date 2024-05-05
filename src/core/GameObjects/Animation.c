#include "Animation.h"

#include <stdlib.h>
#include <string.h>

#include <Config.h>
#include <TextureManager.h>

// AnimationFrame
// Private
static inline AnimationFrame *AnimationFrame_New(SDL_Texture *data) {
    AnimationFrame *animation_frame = (AnimationFrame *) malloc(sizeof(AnimationFrame));
    memset(animation_frame, 0, sizeof(AnimationFrame));

    animation_frame->data = data;

    return animation_frame;
}

// Private
static inline void AnimationFrame_Destroy(AnimationFrame *animation_frame) {
    // All the textures will be released by the Texture Manager
    free(animation_frame);
}

// Private
static inline void Animation_PushFrame(Animation *animation, AnimationFrame *animation_frame) {
    if (animation->_begin == NULL) {
        animation->_begin = animation_frame;
    }

    if (animation->_end != NULL) {
        animation->_end->next = animation_frame;
    }

    animation->_end = animation_frame;
}

// Animation
/*
 Parameters:
    frame_count    how much frames will have the animation
    ...            va_list with the texture name of each frame
 Remarks:
    The size of the first frame will be the size of the entire animation
    this will have effect in its use i.e. in an Animated Sprite
    An animation object must be released separately of an Animated Sprite object
    Default duration per frame is calculated to be 24 fps
 */
Animation *Animation_New(int frame_count, ...) {
    Animation *animation = (Animation *) malloc(sizeof(Animation));
    memset(animation, 0, sizeof(Animation));

    animation->frame_count = frame_count;
    animation->duration_per_frame = ANIMATION_FRAME_DURATION(frame_count);

    va_list frame_list;
    va_start(frame_list, frame_count);

    for (int i=0; i<frame_count; i++) {
        char *texture_name = va_arg(frame_list, char*);

        // If the texture name is valid
        if (texture_name != NULL) {
            SDL_Rect rect;
            SDL_Texture *data = TextureManager_Get(texture_name, &rect);

            // If the texture is available
            if (data != NULL) {
                // Create a new frame and push into the list
                AnimationFrame *frame = AnimationFrame_New(data);
                Animation_PushFrame(animation, frame);

                // If the frame is the first frame use its size for the entire animation
                if (i == 0) {
                    GameObject_SetSize(GAME_OBJECT(animation), rect.w, rect.h);
                }
            }
        }
    }

    va_end(frame_list);

    return animation;
}

void Animation_Destroy(Animation *animation) {
    AnimationFrame *frame = animation->_begin;
    AnimationFrame *next;

    while (frame != NULL) {
        next = frame->next;
        AnimationFrame_Destroy(frame);
        frame = next;
    }

    free(animation);
}

// Setters

inline void Animation_SetDurationPerFrame(Animation *animation, float value) {
    animation->duration_per_frame = value;
}

// Getters

inline float Animation_GetDurationPerFrame(Animation *animation) {
    return animation->duration_per_frame;
}

inline float Animation_GetDuration(Animation *animation) {
    return animation->duration_per_frame * animation->frame_count;
}
