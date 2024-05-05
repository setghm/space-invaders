#include "Enemy.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Bullets.h"
#include "../Global.h"

Enemy *Enemy_New(int id) {
	Enemy *enemy = (Enemy *) malloc(sizeof(Enemy));
	memset(enemy, 0, sizeof(Enemy));

	enemy->id = id;
	enemy->sprite = AnimatedSprite_New();
	enemy->animations.idle = Animation_New(2, "enemy 1", "enemy 2");
	enemy->animations.explosion = Animation_New(4, "explode 1", "explode 2", "explode 3", "explode 4");

	Animation_SetDurationPerFrame(enemy->animations.idle, ENEMY_FRAME_DURATION);
	Animation_SetDurationPerFrame(enemy->animations.explosion, EXPLOSION_FRAME_DURATION);

	AnimatedSprite_SetAnimation(enemy->sprite, enemy->animations.idle);

	Sprite_SetBoxSize(SPRITE(enemy->sprite), ENEMY_WIDTH, ENEMY_HEIGHT);
	Sprite_SetBoxOffsetX(SPRITE(enemy->sprite), ENEMY_OFFSET_X);
	Sprite_SetBoxOffsetY(SPRITE(enemy->sprite), ENEMY_OFFSET_Y);

	enemy->time_to_delete = TIME_TO_DELETE;
	enemy->state = ENEMY_STATE_ALIVE;

	enemy->shoot_time.min_secs = ENEMY_FIRE_MIN_TIME;
	enemy->shoot_time.max_secs = ENEMY_FIRE_MAX_TIME;

	return enemy;
}

void Enemy_SetPosition(Enemy *enemy, float x, float y) {
	Sprite_SetPosition(SPRITE(enemy->sprite), x, y);
}

void Enemy_Shoot(Enemy *enemy) {
	Bullets_Shoot(ENEMY_BULLET, Sprite_GetBody(SPRITE(enemy->sprite)));
	SoundManager_Play("enemy shoot", SOUND_EFFECTS_VOLUME, false);
}

void Enemy_ResetTimeToShoot(Enemy *enemy) {
	int min_ms = (int) enemy->shoot_time.min_secs * 1000;
	int max_ms = (int) enemy->shoot_time.max_secs * 1000;
	int millis = RAND_RANGE(min_ms, max_ms);

	enemy->time_to_shoot = millis / 1000.0f;
}

void Enemy_SetTimeToShootRange(Enemy *enemy, float min_secs, float max_secs) {
	enemy->shoot_time.min_secs = min_secs;
	enemy->shoot_time.max_secs = max_secs;
}

void Enemy_SetVelocityYInRange(Enemy *enemy, float min_pps, float max_pps) {
	int min = (int) min_pps * 10;
	int max = (int) max_pps * 10;
	float y = RAND_RANGE(min, max) / 10.0f;

	Sprite_SetVelocityY(SPRITE(enemy->sprite), y);
}

void Enemy_SetVelocityXInRange(Enemy *enemy, float min_pps, float max_pps) {
	int min = (int) min_pps * 10;
	int max = (int) max_pps * 10;
	float x = RAND_RANGE(min, max) / 10.0f;

	Sprite_SetVelocityX(SPRITE(enemy->sprite), x);
}

void Enemy_Update(Enemy *enemy, SDL_Renderer *renderer, float delta_time) {
    Sprite_Update(SPRITE(enemy->sprite), delta_time);
	AnimatedSprite_Draw(enemy->sprite, renderer);

	if (enemy->state == ENEMY_STATE_EXPLODING) {
		enemy->time_to_delete -= delta_time;

		if (enemy->time_to_delete <= 0) {
			enemy->state = ENEMY_STATE_DEATH;
		}
	} else if (enemy->state == ENEMY_STATE_ALIVE) {
		enemy->time_to_shoot -= delta_time;

		if (enemy->time_to_shoot <= 0) {
			Enemy_Shoot(enemy);
			Enemy_ResetTimeToShoot(enemy);
		}
	}
}

void Enemy_Destroy(Enemy *enemy) {
	if (enemy->sprite) {
		AnimatedSprite_Destroy(enemy->sprite);
	}
	if (enemy->animations.idle) {
		Animation_Destroy(enemy->animations.idle);
	}
	if (enemy->animations.explosion) {
		Animation_Destroy(enemy->animations.explosion);
	}

	free(enemy);
}

