#include "GroupAttack.h"

#include "../Global.h"
#include "Enemy.h"
#include "Enemies.h"
#include "EnemiesList.h"

void GroupAttack_Start() {
	int rows = RAND_RANGE(ENEMIES_ATTACK_MIN_ROWS, ENEMIES_ATTACK_MAX_ROWS);
	float start_y = -(rows * (ENEMY_HEIGHT + ENEMIES_SPACE_BETWEEN_Y));

	for (int i=0; i<rows; i++) {
		for (int j=0; j<ENEMIES_IN_ROW; j++) {
			float x = ENEMIES_MARGIN_HORIZONTAL + (ENEMY_WIDTH + ENEMIES_SPACE_BETWEEN_X) * j;
			float y = ENEMIES_MARGIN_VERTICAL + (ENEMY_HEIGHT + ENEMIES_SPACE_BETWEEN_Y) * i;

			Enemy *enemy = Enemy_New(i * ENEMIES_IN_ROW + j);
			Enemy_SetTimeToShootRange(enemy, GROUP_ATTACK_FIRE_MIN_TIME, GROUP_ATTACK_FIRE_MAX_TIME);
			Enemy_ResetTimeToShoot(enemy);
			EnemiesList_Push(Enemies_GetList(), enemy);
			Enemy_SetPosition(enemy, x, start_y + y);

			// Start the entrance
            Sprite_SetVelocityY(SPRITE(enemy->sprite), ENEMIES_ENTRANCE_VELOCITY);
		}
	}

	Enemies_SetState(ENEMIES_STATE_ARRIVING);
}

void GroupAttack_Arrive(SDL_Renderer *renderer, float delta_time) {
	bool arrived = false;

	// Update the entrance
	Enemy *enemy = Enemies_GetList()->first;

	while (enemy) {
		int row = (int)(enemy->id / ENEMIES_IN_ROW);
		float y = Sprite_GetY(SPRITE(enemy->sprite));
		float target_y = ENEMIES_MARGIN_VERTICAL + row * (ENEMY_HEIGHT + ENEMIES_SPACE_BETWEEN_Y);

		if (roundf(y) >= target_y) {
			arrived = true;
		}
		enemy = enemy->next;
	}

	// Stop the entrance
	if (arrived) {
		enemy = Enemies_GetList()->first;

		while (enemy) {
			Sprite_SetVelocityY(SPRITE(enemy->sprite), 0);
			enemy = enemy->next;
		}

		Enemies_SetState(ENEMIES_STATE_ATTACKING);
	}

	GroupAttack_Attack(renderer, delta_time);
}

void GroupAttack_Attack(SDL_Renderer *renderer, float delta_time) {
	Enemies_UpdateEnemies(renderer, delta_time);

	if (Enemies_GetCount() == 0) {
		Enemies_SetState(ENEMIES_STATE_REGENERATING);
	}
}
