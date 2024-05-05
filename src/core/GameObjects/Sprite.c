#include "Sprite.h"

#include <stdlib.h>
#include <string.h>

#include <Config.h>
#include <TextureManager.h>

extern void Image_DefaultInit(Image *image);
extern void Image_SetSize(Image *image, float w, float h);

// Private
void Sprite_DefaultInit(Sprite *sprite) {
    Image_DefaultInit(IMAGE(sprite));
    Sprite_SetCollisionsEnabled(sprite, SPRITE_COLLISIONS_ENABLED_BY_DEFAULT);
}

// Private
void Sprite_SetSize(Sprite *sprite, float w, float h) {
    Image_SetSize(IMAGE(sprite), w, h);

    // Commented to allow custom collision boxes
    //PhysicsBody_SetBoxSize(&sprite->body, Sprite_GetDisplayWidth(sprite), Sprite_GetDisplayHeight(sprite));
}

Sprite *Sprite_New(const char* texture_name) {
    Sprite *sprite = (Sprite *) malloc(sizeof(Sprite));
    memset(sprite, 0, sizeof(Sprite));

    SDL_Rect rect;

    Sprite_SetTexture(sprite, TextureManager_Get(texture_name, &rect));
    Sprite_SetSize(sprite, (float) rect.w, (float) rect.h);
    Sprite_DefaultInit(sprite);

#ifdef DEBUG
    if (Sprite_GetTexture(sprite) == NULL) {
        fprintf(stderr, "ERROR: Texture \"%s\" is not loaded\n", texture_name);
    }
#endif

    return sprite;
}

// Override
void Sprite_Draw(Sprite *sprite, SDL_Renderer *renderer) {
    // Don't draw if the sprite is not visible
    if (!Image_IsVisible(IMAGE(sprite))) return;

    // Apply scale and pivot offset (origin)
    SDL_Rect transformations = {
        (int) roundf(Sprite_GetX(sprite)),
        (int) roundf(Sprite_GetY(sprite)),
        (int) roundf(Sprite_GetDisplayWidth(sprite)),
        (int) roundf(Sprite_GetDisplayHeight(sprite))
    };

	// Draw the sprite
    SDL_RenderCopy(renderer, Sprite_GetTexture(sprite), NULL, &transformations);

#ifdef DEBUG_PHYSICS
	// Draw the collision box
    PhysicsBody_DebugDraw(&sprite->body, renderer);
#endif
}

inline void Sprite_Update(Sprite *sprite, float delta_time) {
    PhysicsBody_Update(&sprite->body, delta_time);
}

inline void Sprite_Destroy(Sprite *sprite) {
    Image_Destroy(IMAGE(sprite));
}

// Setters

inline void Sprite_SetVelocityX(Sprite *sprite, float velocity) {
    PhysicsBody_SetVelocityX(&sprite->body, velocity);
}

inline void Sprite_SetVelocityY(Sprite *sprite, float velocity) {
    PhysicsBody_SetVelocityY(&sprite->body, velocity);
}

inline bool Sprite_CollisionWith(Sprite *target, Sprite *collider) {
    return PhysicsBody_CollisionWith(&target->body, &collider->body);
}

// Override
void Sprite_SetX(Sprite *sprite, float x) {
    // Get the position without origin transformations
    float subtract = Sprite_GetDisplayWidth(sprite) * Sprite_GetOriginX(sprite);
    PhysicsBody_SetX(&sprite->body, x - subtract);
}

// Override
void Sprite_SetY(Sprite *sprite, float y) {
    // Get the position without origin transformations
    float subtract = Sprite_GetDisplayHeight(sprite) * Sprite_GetOriginY(sprite);
    PhysicsBody_SetY(&sprite->body, y - subtract);
}

inline void Sprite_SetPosition(Sprite *sprite, float x, float y) {
    Sprite_SetX(sprite, x);
    Sprite_SetY(sprite, y);
}

inline void Sprite_SetOriginX(Sprite *sprite, float x) {
    Image_SetOriginX(IMAGE(sprite), x);
}

inline void Sprite_SetOriginY(Sprite *sprite, float y) {
    Image_SetOriginY(IMAGE(sprite), y);
}

inline void Sprite_SetOrigin(Sprite *sprite, float x, float y) {
    Image_SetOrigin(IMAGE(sprite), x, y);
}

inline void Sprite_SetScale(Sprite *sprite, float scale) {
    Image_SetScale(IMAGE(sprite), scale);
    PhysicsBody_SetScale(&sprite->body, scale);
}

inline void Sprite_SetTexture(Sprite *sprite, SDL_Texture *texture) {
    Image_SetTexture(IMAGE(sprite), texture);
}

inline void Sprite_SetWorldBounds(Sprite *sprite, float x1, float y1, float x2, float y2) {
    PhysicsBody_SetWorldBounds(&sprite->body, x1, y1, x2, y2);
}

inline void Sprite_SetWorldBoundsOn(Sprite *sprite, bool turn_on) {
    PhysicsBody_SetWorldBoundsOn(&sprite->body, turn_on);
}

inline void Sprite_SetVisible(Sprite *sprite, bool show) {
    Image_SetVisible(IMAGE(sprite), show);
}

inline void Sprite_SetCollisionsEnabled(Sprite *sprite, bool enabled) {
    sprite->body.collisions_enabled = enabled;
}

inline void Sprite_SetBoxSize(Sprite *sprite, float w, float h) {
    PhysicsBody_SetBoxSize(&sprite->body, w, h);
}

inline void Sprite_SetBoxOffsetX(Sprite *sprite, float x) {
    PhysicsBody_SetBoxOffsetX(&sprite->body, x);
}

inline void Sprite_SetBoxOffsetY(Sprite *sprite, float y) {
    PhysicsBody_SetBoxOffsetY(&sprite->body, y);
}

// Getters

// Private
float Sprite_GetBodyX(Sprite *sprite) {
    return PhysicsBody_GetX(&sprite->body);
}

// Private
float Sprite_GetBodyY(Sprite *sprite) {
    return PhysicsBody_GetY(&sprite->body);
}

// Override
inline float Sprite_GetX(Sprite *sprite) {
    return PhysicsBody_GetX(&sprite->body);
}

// Override
inline float Sprite_GetY(Sprite *sprite) {
    return PhysicsBody_GetY(&sprite->body);
}

inline float Sprite_GetOriginX(Sprite *sprite) {
    return Image_GetOriginX(IMAGE(sprite));
}

inline float Sprite_GetOriginY(Sprite *sprite) {
    return Image_GetOriginY(IMAGE(sprite));
}

inline float Sprite_GetScale(Sprite *sprite) {
    return Image_GetScale(IMAGE(sprite));
}

inline SDL_Texture *Sprite_GetTexture(Sprite *sprite) {
    return Image_GetTexture(IMAGE(sprite));
}

inline float Sprite_GetDisplayWidth(Sprite *sprite) {
    return Image_GetDisplayWidth(IMAGE(sprite));
}

inline float Sprite_GetDisplayHeight(Sprite *sprite) {
    return Image_GetDisplayHeight(IMAGE(sprite));
}

inline bool Sprite_IsVisible(Sprite *sprite) {
    return Image_IsVisible(IMAGE(sprite));
}

inline PhysicsBody *Sprite_GetBody(Sprite *sprite) {
    return &sprite->body;
}
