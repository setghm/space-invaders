#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Engine.h>
#include <GameObjects.h>

static struct _player_prototype_ {
	AnimatedSprite *sprite;

	struct {
		Animation *idle;
		Animation *move;
		Animation *explosion;
	} animations;

	bool fire_charged;
	bool is_death;
	bool can_restart;
	bool respawning;

    float fire_charging_time;
	float respawn_time_left;
	float respawn_blink_time;
	float time_to_delete;
} Player;

void Player_Create();
void Player_Update(SDL_Renderer *renderer, float delta_time);
void Player_Input(const SDL_Event *e);
void Player_Release();

bool Player_CollisionWith(PhysicsBody *collider);
void Player_EnemyCollision();
void Player_WasImpacted();
void Player_Restart();

#endif
