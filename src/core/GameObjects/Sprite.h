#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL.h>
#include "Structs.h"
#include "Image.h"
#include "PhysicsBody.h"

#define SPRITE(s)	((Sprite *) s)

typedef struct _Sprite_ Sprite;

struct _Sprite_ {
    Image super;
    PhysicsBody body;
};

Sprite *Sprite_New(const char* texture_name);
void Sprite_Destroy(Sprite *sprite);
void Sprite_Draw(Sprite *sprite, SDL_Renderer *renderer);
void Sprite_Update(Sprite *sprite, float delta_time);

bool Sprite_CollisionWith(Sprite *target, Sprite *collider);
bool Sprite_CollisionWithGroup(Sprite *sprite, int group_id);

void Sprite_SetX(Sprite *sprite, float x);
void Sprite_SetY(Sprite *sprite, float y);
void Sprite_SetPosition(Sprite *sprite, float x, float y);
void Sprite_SetOriginX(Sprite *sprite, float x);
void Sprite_SetOriginY(Sprite *sprite, float y);
void Sprite_SetOrigin(Sprite *sprite, float x, float y);
void Sprite_SetScale(Sprite *sprite, float scale);
void Sprite_SetTexture(Sprite *sprite, SDL_Texture *texture);
void Sprite_SetWorldBounds(Sprite *sprite, float x1, float y1, float x2, float y2);
void Sprite_SetWorldBoundsOn(Sprite *sprite, bool turn_on);
void Sprite_SetVisible(Sprite *sprite, bool show);
void Sprite_SetCollisionsEnabled(Sprite *sprite, bool enabled);
void Sprite_SetBoxSize(Sprite *sprite, float w, float h);
void Sprite_SetBoxOffsetX(Sprite *sprite, float x);
void Sprite_SetBoxOffsetY(Sprite *sprite, float y);
void Sprite_SetVelocityX(Sprite *sprite, float velocity);
void Sprite_SetVelocityY(Sprite *sprite, float velocity);

SDL_Texture *Sprite_GetTexture(Sprite *sprite);
float Sprite_GetX(Sprite *sprite);
float Sprite_GetY(Sprite *sprite);
float Sprite_GetOriginX(Sprite *sprite);
float Sprite_GetOriginY(Sprite *sprite);
float Sprite_GetScale(Sprite *sprite);
float Sprite_GetDisplayWidth(Sprite *sprite);
float Sprite_GetDisplayHeight(Sprite *sprite);
bool Sprite_IsVisible(Sprite *sprite);
PhysicsBody *Sprite_GetBody(Sprite *sprite);

#endif
