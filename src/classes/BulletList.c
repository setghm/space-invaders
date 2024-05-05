#include "BulletList.h"

void Bullets_PushBack(Bullet *bullet) {
	if (BulletList.first == NULL) {
		BulletList.first = bullet;
	}

	if (BulletList.last != NULL) {
		BulletList.last->next = bullet;
		bullet->prev = BulletList.last;
	}

	BulletList.last = bullet;
}

Bullet *Bullets_Remove(Bullet *target) {
	Bullet *bullet = BulletList.first;
	Bullet *next;

	while (bullet) {
		next = bullet->next;

		if (bullet == target) {
			if (bullet->prev) {
				if (next) {
					bullet->prev->next = next;
					next->prev = bullet->prev;
				} else {
					bullet->prev->next = NULL;
					BulletList.last = bullet->prev;
				}
			} else {
				if (next) {
					next->prev = NULL;
					BulletList.first = next;
				} else {
					BulletList.first = NULL;
					BulletList.last = NULL;
				}
			}

			return bullet;
		}

		bullet = next;
	}

	return NULL;
}

Bullet *Bullets_GetFirst() {
	return BulletList.first;
}
