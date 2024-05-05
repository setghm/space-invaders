#ifndef __BULLET_H__
#define __BULLET_H__

#include <Engine.h>

typedef struct _Bullet_ Bullet;

typedef enum _BulletOwner_ {
	PLAYER_BULLET,
	ENEMY_BULLET
} BulletOwner;

struct _Bullet_ {
	BulletOwner owner;
	union {
		Solid *solid;
		Solid *solids[2];
	};
	Bullet *prev;
	Bullet *next;
};

Bullet *Bullet_New(BulletOwner owner);
void Bullet_Destroy(Bullet *bullet);

#endif
