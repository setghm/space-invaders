#include "Bullet.h"
#include "../Global.h"

Bullet *Bullet_New(BulletOwner owner) {
	Bullet *bullet = (Bullet *) malloc(sizeof(Bullet));
	memset(bullet, 0, sizeof(Bullet));

	bullet->owner = owner;

	if (owner == PLAYER_BULLET) {
		bullet->solids[0] = Solid_New(PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT);
		bullet->solids[1] = Solid_New(PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT);

		Solid_SetColor(bullet->solids[0], 0, 255, 255, 255);
		Solid_SetColor(bullet->solids[1], 0, 255, 255, 255);
	} else {
		bullet->solid = Solid_New(ENEMY_BULLET_WIDTH, ENEMY_BULLET_HEIGHT);

		Solid_SetColor(bullet->solid, 255, 0, 255, 255);
	}

	return bullet;
}

void Bullet_Destroy(Bullet *bullet) {
	if (bullet == NULL) return;

	if (bullet->owner == PLAYER_BULLET) {
        Solid_Destroy(bullet->solids[0]);
        Solid_Destroy(bullet->solids[1]);
	} else {
		Solid_Destroy(bullet->solid);
	}

	free(bullet);
}
