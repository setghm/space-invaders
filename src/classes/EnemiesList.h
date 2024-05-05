#ifndef __ENEMIES_LIST_H__
#define __ENEMIES_LIST_H__

#include <Engine.h>
#include "Enemy.h"

typedef struct _EnemiesList_ EnemiesList;

struct _EnemiesList_ {
	Enemy *first;
	Enemy *last;
	int count;
};

void EnemiesList_Push(EnemiesList *list, Enemy *enemy);
Enemy *EnemiesList_Get(EnemiesList *list, int id);
void EnemiesList_RemoveAll(EnemiesList *list);
void EnemiesList_Remove(EnemiesList *list, int id);

#endif
