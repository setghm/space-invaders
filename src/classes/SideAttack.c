#include "SideAttack.h"
#include "Enemy.h"
#include "Enemies.h"
#include "EnemiesList.h"

#include "../Global.h"

// Private
int side_attack_id;
int side_attack_last_zone;
bool side_attack_generating;

// Private
void SideAttack_AddEnemy() {
	Enemy *enemy = Enemy_New(side_attack_id++);
	Enemy_ResetTimeToShoot(enemy);

    // Divide the y-axis in 3 zones and select one
    int zone;
    do {
        zone = RAND_RANGE(1, 3);
    } while(side_attack_last_zone == zone);
    side_attack_last_zone = zone;

    int min_y, max_y;

    switch(zone) {
    case 1: max_y = ENEMIES_ATTACK_Y_ZONE_1;
            min_y = ENEMIES_ATTACK_MIN_Y; break;
    case 2: max_y = ENEMIES_ATTACK_Y_ZONE_2;
            min_y = ENEMIES_ATTACK_Y_ZONE_1; break;
    case 3: max_y = ENEMIES_ATTACK_Y_ZONE_3;
            min_y = ENEMIES_ATTACK_Y_ZONE_2; break;
    }

	// Generate random position in y
	float y = (float)RAND_RANGE(min_y, max_y);
	Enemy_SetPosition(enemy, ENEMIES_ATTACK_START_X, y);

	// Start moving to right side
    Enemy_SetVelocityXInRange(enemy, ENEMIES_ATTACK_MIN_VELOCITY, ENEMIES_ATTACK_MAX_VELOCITY);

	EnemiesList_Push(Enemies_GetList(), enemy);
}

void SideAttack_CheckEnemiesPosition() {
	Enemy *enemy = Enemies_GetList()->first;
	Enemy *next;

	while (enemy) {
		next = enemy->next;

		float x = Sprite_GetX(SPRITE(enemy->sprite));

		if (x >= ENEMIES_TARGET_X) {
			EnemiesList_Remove(Enemies_GetList(), enemy->id);
		}

		enemy = next;
	}
}

void SideAttack_Start() {
	side_attack_id = 0;
	side_attack_generating = true;
	Enemies_ResetAttackTime();
	Enemies_ResetNextEnemyTime();

	Enemies_SetState(ENEMIES_STATE_ATTACKING);
}

void SideAttack_Attack(SDL_Renderer *renderer, float delta_time) {
	if (side_attack_generating) {
		if (Enemies_GetNextEnemyTime() <= 0) {
			Enemies_ResetNextEnemyTime();
			SideAttack_AddEnemy();
		} else {
			Enemies_UpdateNextEnemyTime(delta_time);
		}

		if (Enemies_GetAttackTime() <= 0) {
			side_attack_generating = false;
		} else {
			Enemies_UpdateAttackTime(delta_time);
		}
	} else {
		if (Enemies_GetCount() == 0) {
			Enemies_SetState(ENEMIES_STATE_REGENERATING);
		}
	}

	// Check position in viewport
	SideAttack_CheckEnemiesPosition();

	Enemies_UpdateEnemies(renderer, delta_time);
}
