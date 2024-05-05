#ifndef __SOLID_H__
#define __SOLID_H__

#include <SDL2/SDL.h>
#include <inttypes.h>
#include "Structs.h"
#include "PhysicsBody.h"

typedef struct _Solid_ Solid;

struct _Solid_ {
	Color color;
	PhysicsBody body;
    bool visible;
};

Solid *Solid_New(float width, float height);
void Solid_Draw(Solid *solid, SDL_Renderer *renderer);
void Solid_Update(Solid *solid, float delta_time);
void Solid_Destroy(Solid *solid);

bool Solid_CollisionWithArea(Solid *solid, SDL_Rect *area);

void Solid_SetPosition(Solid *solid, float x, float y);
void Solid_SetSize(Solid *solid, float width, float height);
void Solid_SetColor(Solid *solid, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void Solid_SetVelocityX(Solid *solid, float vx);
void Solid_SetVelocityY(Solid *solid, float vy);
void Solid_SetVisible(Solid *solid, bool visible);
void Solid_SetCollisionsEnabled(Solid *solid, bool enabled);

float Solid_GetX(Solid *solid);
float Solid_GetY(Solid *solid);
float Solid_GetWidth(Solid *solid);
float Solid_GetHeight(Solid *solid);

#endif
