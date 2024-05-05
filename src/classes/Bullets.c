#include "Bullets.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GameObjects.h>

#include "../Global.h"
#include "Enemies.h"
#include "Player.h"

SDL_Rect WORLD_AREA = {
	0, 0, WINDOW_WIDTH, WINDOW_HEIGHT
};

void Bullets_Shoot(BulletOwner owner, PhysicsBody *owner_body) {
	Bullet *bullet = Bullet_New(owner);

	int x = owner_body->box.x;
	int y = owner_body->box.y;

	// Set velocity, position and add to a collision group
	if (owner == PLAYER_BULLET) {
		Solid_SetVelocityY(bullet->solids[0], PLAYER_BULLET_VELOCITY);
		Solid_SetVelocityY(bullet->solids[1], PLAYER_BULLET_VELOCITY);

		int x0 = x + PLAYER_BULLET_0_X;
		int y0 = y + PLAYER_BULLET_0_Y;
		int x1 = x + PLAYER_BULLET_1_X;
		int y1 = y + PLAYER_BULLET_1_Y;

		Solid_SetPosition(bullet->solids[0], x0, y0);
		Solid_SetPosition(bullet->solids[1], x1, y1);
	} else {
        float vy = (float) RAND_RANGE(ENEMY_BULLET_VELOCITY_MIN, ENEMY_BULLET_VELOCITY_MAX);
		Solid_SetVelocityY(bullet->solid, vy);

		x += ENEMY_BULLET_X;
		y += ENEMY_BULLET_Y;

		Solid_SetPosition(bullet->solid, x, y);
	}

	// Insert into the bullet list
	Bullets_PushBack(bullet);
}

void Bullets_Update(SDL_Renderer *renderer, float delta_time) {
	Bullet *bullet = Bullets_GetFirst();
	Bullet *next;

	while (bullet) {
        next = bullet->next;

		// Update and draw the bullets
		if (bullet->owner == PLAYER_BULLET) {
            Solid_Update(bullet->solids[0], delta_time);
            Solid_Update(bullet->solids[1], delta_time);

            Solid_Draw(bullet->solids[0], renderer);
            Solid_Draw(bullet->solids[1], renderer);

			// Check viewport position
			if (bullet->solids[0]->visible) {
				if (!Solid_CollisionWithArea(bullet->solids[0], &WORLD_AREA)) {
					Bullet *removed = Bullets_Remove(bullet);
					Bullet_Destroy(removed);
				}
			} else if (bullet->solids[1]->visible) {
				if (!Solid_CollisionWithArea(bullet->solids[1], &WORLD_AREA)) {
					Bullet *removed = Bullets_Remove(bullet);
					Bullet_Destroy(removed);
				}
			} else {
				Bullet *removed = Bullets_Remove(bullet);
				Bullet_Destroy(removed);
			}
		} else {
            Solid_Update(bullet->solid, delta_time);

            Solid_Draw(bullet->solid, renderer);

			// Check viewport position
			if (!Solid_CollisionWithArea(bullet->solid, &WORLD_AREA)) {
				Bullet *removed = Bullets_Remove(bullet);
				Bullet_Destroy(removed);
			}
		}

		bullet = next;
	}
}

void Bullets_Release() {
	Bullet *bullet = Bullets_GetFirst();
	Bullet *next;

	while (bullet) {
		next = bullet->next;
		Bullet_Destroy(bullet);
		bullet = next;
	}
}

void Bullets_PlayerBulletEnemyCollision() {
	Bullet *bullet = Bullets_GetFirst();

	while (bullet) {
		if (bullet->owner == PLAYER_BULLET) {
			int enemy_one = -1, enemy_two = -1;

			if (bullet->solids[0]->visible) {
				enemy_one = Enemies_CollisionWith(&bullet->solids[0]->body);
			}
			if (bullet->solids[1]->visible) {
				enemy_two = Enemies_CollisionWith(&bullet->solids[1]->body);
			}

			if (enemy_one == enemy_two && enemy_one != -1) {
				Enemies_WasImpacted(enemy_one);
				Solid_SetCollisionsEnabled(bullet->solids[0], false);
				Solid_SetVisible(bullet->solids[0], false);
				Solid_SetCollisionsEnabled(bullet->solids[1], false);
				Solid_SetVisible(bullet->solids[1], false);
			} else {
				if (enemy_one != -1) {
					Enemies_WasImpacted(enemy_one);
                    Solid_SetCollisionsEnabled(bullet->solids[0], false);
					Solid_SetVisible(bullet->solids[0], false);
				}
				if (enemy_two != -1) {
					Enemies_WasImpacted(enemy_two);
					Solid_SetCollisionsEnabled(bullet->solids[1], false);
					Solid_SetVisible(bullet->solids[1], false);
				}
			}
		}

		bullet = bullet->next;
	}
}

void Bullets_EnemyBulletPlayerCollision() {
	Bullet *bullet = Bullets_GetFirst();

	while (bullet) {
		if (bullet->owner == ENEMY_BULLET) {
			if (Player_CollisionWith(&bullet->solid->body)) {
				Player_WasImpacted();
				Solid_SetCollisionsEnabled(bullet->solid, false);
				Solid_SetVisible(bullet->solid, false);
				break;
			}
		}
		bullet = bullet->next;
	}

}
