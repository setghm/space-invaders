#ifndef __BULLETS_H__
#define __BULLETS_H__

#include <Engine.h>
#include "Bullet.h"
#include "BulletList.h"

void Bullets_Shoot(BulletOwner owner, PhysicsBody *owner_body);
void Bullets_Update(SDL_Renderer *renderer, float delta_time);
void Bullets_Release();

void Bullets_PlayerBulletEnemyCollision();
void Bullets_EnemyBulletPlayerCollision();

#endif
