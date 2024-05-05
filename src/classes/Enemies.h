#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include <Engine.h>
#include "EnemiesList.h"

typedef enum _AttackType_ {
	ATTACK_TYPE_GROUP,
	ATTACK_TYPE_BURST,
	ATTACK_TYPE_SIDE
} AttackType;

typedef enum _EnemiesState_ {
	ENEMIES_STATE_ARRIVING,
	ENEMIES_STATE_ATTACKING,
	ENEMIES_STATE_REGENERATING
} EnemiesState;

static struct _Enemies_ {
	EnemiesList list;

	AttackType attack;
	int last_attack;
	float attack_time;

	float next_enemy_time;
	float regenerating_time;

	EnemiesState state;
} Enemies;

// Enemies class
void Enemies_Create();
void Enemies_StartAttack();
void Enemies_Update(SDL_Renderer *renderer, float delta_time);
void Enemies_UpdateEnemies(SDL_Renderer *renderer, float delta_time);
void Enemies_Release();

int Enemies_CollisionWith(PhysicsBody *collider);
void Enemies_WasImpacted(int id);

// Getters and setters
int Enemies_GetCount();
float Enemies_GetAttackTime();
float Enemies_GetNextEnemyTime();
EnemiesList *Enemies_GetList();

void Enemies_SetState(EnemiesState state);
EnemiesState Enemies_GetState();

// Timers
void Enemies_ResetAttackTime();
void Enemies_UpdateAttackTime(float delta_time);

void Enemies_ResetNextEnemyTime();
void Enemies_UpdateNextEnemyTime(float delta_time);

#endif
