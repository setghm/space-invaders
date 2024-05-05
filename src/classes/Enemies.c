#include "Enemies.h"
#include "../Global.h"
#include "GroupAttack.h"
#include "BurstAttack.h"
#include "SideAttack.h"
#include "Enemy.h"
#include "Score.h"

void Enemies_Create() {
	Enemies.last_attack = -1;
	Enemies_StartAttack();
}

void Enemies_StartAttack() {
	do {
		Enemies.attack = RAND_RANGE(ATTACK_TYPE_GROUP, ATTACK_TYPE_SIDE);
	} while (Enemies.attack == Enemies.last_attack);

	Enemies.last_attack = Enemies.attack;

	switch (Enemies.attack) {
		case ATTACK_TYPE_GROUP:
			GroupAttack_Start();
			break;
		case ATTACK_TYPE_BURST:
			BurstAttack_Start();
			break;
		case ATTACK_TYPE_SIDE:
			SideAttack_Start();
			break;
	}
}

void Enemies_Update(SDL_Renderer *renderer, float delta_time) {
	if (Enemies.state == ENEMIES_STATE_REGENERATING) {
		Enemies.regenerating_time -= delta_time;

		if (Enemies.regenerating_time <= 0) {
			Enemies_StartAttack();
		}
	} else if (Enemies.state == ENEMIES_STATE_ARRIVING) {
		GroupAttack_Arrive(renderer, delta_time);
	} else {
		switch (Enemies.attack) {
			case ATTACK_TYPE_GROUP:
				GroupAttack_Attack(renderer, delta_time);
				break;
			case ATTACK_TYPE_BURST:
				BurstAttack_Attack(renderer, delta_time);
				break;
			case ATTACK_TYPE_SIDE:
				SideAttack_Attack(renderer, delta_time);
				break;
		}
	}
}

void Enemies_UpdateEnemies(SDL_Renderer *renderer, float delta_time) {
	// Update and draw each enemy in the linked list
	Enemy *enemy = Enemies.list.first;
	Enemy *next;

	while (enemy) {
		next = enemy->next;
		if (enemy->state != ENEMY_STATE_DEATH) {
			Enemy_Update(enemy, renderer, delta_time);
		} else {
			EnemiesList_Remove(Enemies_GetList(), enemy->id);
		}
		enemy = next;
	}

}

inline void Enemies_Release() {
	EnemiesList_RemoveAll(&Enemies.list);
}

int Enemies_CollisionWith(PhysicsBody *collider) {
	Enemy *enemy = Enemies.list.first;

	while (enemy) {
		PhysicsBody *target = Sprite_GetBody(SPRITE(enemy->sprite));

		if (PhysicsBody_CollisionWith(target, collider)) {
			return enemy->id;
		}

		enemy = enemy->next;
	}

	return -1;
}

void Enemies_WasImpacted(int id) {
	Enemy *enemy = EnemiesList_Get(&Enemies.list, id);

	if (enemy) {
		Sprite_SetCollisionsEnabled(SPRITE(enemy->sprite), false);
		AnimatedSprite_SetAnimation(enemy->sprite, enemy->animations.explosion);
		enemy->state = ENEMY_STATE_EXPLODING;

		Score_Increment();
		SoundManager_Play("enemy die", SOUND_EFFECTS_VOLUME, false);
	}
}

void Enemies_ResetAttackTime() {
	int min_ms = (int) ENEMIES_ATTACK_MIN_TIME * 1000;
	int max_ms = (int) ENEMIES_ATTACK_MAX_TIME * 1000;
	int millis = RAND_RANGE(min_ms, max_ms);

	Enemies.attack_time = (float) millis / 1000.0f;
}

void Enemies_UpdateAttackTime(float delta_time) {
	Enemies.attack_time -= delta_time;
}

void Enemies_ResetNextEnemyTime() {
	int min_ms = (int) ENEMIES_TIME_GEN_MIN * 1000;
	int max_ms = (int) ENEMIES_TIME_GEN_MAX * 1000;
	int millis = RAND_RANGE(min_ms, max_ms);

	Enemies.next_enemy_time = (float) millis / 1000.0f;
}

void Enemies_UpdateNextEnemyTime(float delta_time) {
	Enemies.next_enemy_time -= delta_time;
}

/* vvvvvvvvvvvvvvvvvvvvvvvv GETTERS AND SETTERS vvvvvvvvvvvvvvvvvvvvvvvv */

int Enemies_GetCount() {
	return Enemies.list.count;
}

float Enemies_GetAttackTime() {
	return Enemies.attack_time;
}

float Enemies_GetNextEnemyTime() {
	return Enemies.next_enemy_time;
}

EnemiesList *Enemies_GetList() {
	return &Enemies.list;
}

void Enemies_SetState(EnemiesState state) {
	Enemies.state = state;

	if (state == ENEMIES_STATE_REGENERATING) {
		Enemies.regenerating_time = ENEMIES_REGENERATING_TIME;
	}
}

EnemiesState Enemies_GetState() {
	return Enemies.state;
}
