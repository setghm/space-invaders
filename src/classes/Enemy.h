#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <Engine.h>

typedef struct _Enemy_ Enemy;

typedef enum _EnemyState_ {
	ENEMY_STATE_ALIVE,
	ENEMY_STATE_DEATH,
	ENEMY_STATE_EXPLODING
} EnemyState;

struct _Enemy_ {
	int id;

	AnimatedSprite *sprite;
	struct {
		Animation *idle;
		Animation *explosion;
	} animations;

	EnemyState state;

	struct {
		float min_secs;
		float max_secs;
	} shoot_time;

	float time_to_shoot;
	float time_to_delete;

	Enemy *prev;
	Enemy *next;
};

Enemy *Enemy_New(int id);
void Enemy_Update(Enemy *enemy, SDL_Renderer *renderer, float delta_time);
void Enemy_Destroy(Enemy *enemy);

void Enemy_Shoot(Enemy *enemy);
void Enemy_ResetTimeToShoot(Enemy *enemy);

void Enemy_SetTimeToShootRange(Enemy *enemy, float min_secs, float max_secs);
void Enemy_SetPosition(Enemy *enemy, float x, float y);
void Enemy_SetVelocityYInRange(Enemy *enemy, float min_pps, float max_pps);
void Enemy_SetVelocityXInRange(Enemy *enemy, float min_pps, float max_pps);

#endif
