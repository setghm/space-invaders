#include "EnemiesList.h"

void EnemiesList_Push(EnemiesList *list, Enemy *enemy) {
	if (list->first == NULL) {
		list->first = enemy;
	}

	if (list->last != NULL) {
		list->last->next = enemy;
		enemy->prev = list->last;
	}

	list->last = enemy;
	list->count++;
}

Enemy *EnemiesList_Get(EnemiesList *list, int id) {
	Enemy *enemy = list->first;

	while (enemy) {
		if (enemy->id == id) {
			return enemy;
		}
		enemy = enemy->next;
	}

	return NULL;
}

void EnemiesList_RemoveAll(EnemiesList *list) {
	Enemy *enemy = list->first;
    Enemy *next;

    while (enemy) {
        next = enemy->next;
        Enemy_Destroy(enemy);
        enemy = next;
    }

	list->first = NULL;
	list->last = NULL;
	list->count = 0;
}

void EnemiesList_Remove(EnemiesList *list, int id) {
	Enemy *enemy = list->first;
	Enemy *next;

	while (enemy) {
		next = enemy->next;

		if (enemy->id == id) {
			if (enemy->prev) {
				if (enemy->next) {
					next->prev = enemy->prev;
					enemy->prev->next = next;
				} else {
					list->last = enemy->prev;
					enemy->prev->next = NULL;
				}
			} else {
				if (enemy->next) {
					list->first = next;
					next->prev = NULL;
				} else {
					list->first = NULL;
					list->last = NULL;
				}
			}

			Enemy_Destroy(enemy);
			list->count--;
		}

		enemy = next;
	}
}

