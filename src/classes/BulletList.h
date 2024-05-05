#ifndef __BULLET_LIST_H__
#define __BULLET_LIST_H__

#include <Engine.h>
#include "Bullet.h"

static struct {
	Bullet *first;
	Bullet *last;
} BulletList;

void Bullets_PushBack(Bullet *bullet);
Bullet *Bullets_Remove(Bullet *target);
Bullet *Bullets_GetFirst();

#endif
