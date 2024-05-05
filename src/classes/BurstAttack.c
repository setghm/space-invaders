#include "BurstAttack.h"
#include "Enemy.h"
#include "Enemies.h"
#include "EnemiesList.h"

#include "../Global.h"

// Private
int burst_attack_id;
int burst_attack_last_zone;
bool burst_attack_generating;

// Private
void BurstAttack_AddEnemy() {
	Enemy *enemy = Enemy_New(burst_attack_id++);
	Enemy_ResetTimeToShoot(enemy);
	EnemiesList_Push(Enemies_GetList(), enemy);

    // Divide the x-axis in 3 zones and select one
    int zone;
    do {
        zone = RAND_RANGE(1, 3);
    } while(burst_attack_last_zone == zone);
    burst_attack_last_zone = zone;

    int min_x, max_x;

    switch(zone) {
        case 1: max_x = ENEMIES_ATTACK_X_ZONE_1;
                min_x = ENEMIES_ATTACK_X_ZONE_0; break;
        case 2: max_x = ENEMIES_ATTACK_X_ZONE_2;
                min_x = ENEMIES_ATTACK_X_ZONE_1; break;
        case 3: max_x = ENEMIES_ATTACK_X_ZONE_3;
                min_x = ENEMIES_ATTACK_X_ZONE_2; break;
    }

	// Generate random position in x
	float x = (float)RAND_RANGE(min_x, max_x);
	Enemy_SetPosition(enemy, x, ENEMIES_ATTACK_START_Y);

	// Start moving to downside
    Enemy_SetVelocityYInRange(enemy, ENEMIES_ATTACK_MIN_VELOCITY, ENEMIES_ATTACK_MAX_VELOCITY);
}

void BurstAttack_CheckEnemiesPosition() {
	Enemy *enemy = Enemies_GetList()->first;
	Enemy *next;

	while (enemy) {
		next = enemy->next;

		float y = Sprite_GetY(SPRITE(enemy->sprite));
		if (y >= ENEMIES_TARGET_Y) {
			EnemiesList_Remove(Enemies_GetList(), enemy->id);
		}

		enemy = next;
	}
}

void BurstAttack_Start() {
	burst_attack_id = 0;
	burst_attack_generating = true;
    burst_attack_last_zone = -1;
	Enemies_ResetAttackTime();
	Enemies_ResetNextEnemyTime();

	Enemies_SetState(ENEMIES_STATE_ATTACKING);
}

void BurstAttack_Attack(SDL_Renderer *renderer, float delta_time) {
	if (burst_attack_generating) {
		if (Enemies_GetNextEnemyTime() <= 0) {
			Enemies_ResetNextEnemyTime();
			// Generate a new enemy
			BurstAttack_AddEnemy();
		} else {
			Enemies_UpdateNextEnemyTime(delta_time);
		}

		if (Enemies_GetAttackTime() <= 0) {
			burst_attack_generating = false;
		} else {
			Enemies_UpdateAttackTime(delta_time);
		}
	} else {
		if (Enemies_GetCount() == 0) {
			Enemies_SetState(ENEMIES_STATE_REGENERATING);
		}
	}

	// Check position in viewport
	BurstAttack_CheckEnemiesPosition();

	Enemies_UpdateEnemies(renderer, delta_time);
}
