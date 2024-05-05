#ifndef __PHYSICS_BODY__
#define __PHYSICS_BODY__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Structs.h"

typedef struct _PhysicsBody_ PhysicsBody;

struct _PhysicsBody_ {
    Box2 box;
    Vec2 velocity;
    Vec2 box_offset;
    Box2 world_bounds;
    bool world_bounds_on;
    bool collisions_enabled;
};

//void PhysicsBody_AddToCollisionGroup(PhysicsBody *body, int group_id);
//bool PhysicsBody_CollisionWithGroup(PhysicsBody *target, int group_id);
bool PhysicsBody_CollisionWith(PhysicsBody *target, PhysicsBody *collider);
bool PhysicsBody_CollisionWithArea(PhysicsBody *target, SDL_Rect *area);
void PhysicsBody_Update(PhysicsBody *body, float delta_time);
void PhysicsBody_DebugDraw(PhysicsBody *body, SDL_Renderer *renderer);

void PhysicsBody_SetBoxSize(PhysicsBody *body, float w, float h);
void PhysicsBody_SetBoxOffsetX(PhysicsBody *body, float x);
void PhysicsBody_SetBoxOffsetY(PhysicsBody *body, float y);
void PhysicsBody_SetX(PhysicsBody *body, float x);
void PhysicsBody_SetY(PhysicsBody *body, float y);
void PhysicsBody_SetVelocityX(PhysicsBody *body, float x);
void PhysicsBody_SetVelocityY(PhysicsBody *body, float y);
void PhysicsBody_SetWorldBounds(PhysicsBody *body, float x1, float y1, float x2, float y2);
void PhysicsBody_SetWorldBoundsOn(PhysicsBody *body, bool turnon);
void PhysicsBody_SetScale(PhysicsBody *body, float scale);
void PhysicsBody_SetCollisionsEnabled(PhysicsBody *body, bool enabled);

float PhysicsBody_GetBoxOffsetX(PhysicsBody *body);
float PhysicsBody_GetBoxOffsetY(PhysicsBody *body);
float PhysicsBody_GetX(PhysicsBody *body);
float PhysicsBody_GetY(PhysicsBody *body);
float PhysicsBody_GetVelocityX(PhysicsBody *body);
float PhysicsBody_GetVelocityY(PhysicsBody *body);

#endif
