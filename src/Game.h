#ifndef __GAME_H__
#define __GAME_H__

#include <Engine.h>

typedef enum _GameState_ {
	GAME_STATE_INITIAL,
	GAME_STATE_PLAYING,
	GAME_STATE_RESTART
} GameState;

static struct _Game_Prototype_ {
	GameState state;
} Game;

void Game_Preload();
void Game_Create();
void Game_Update(SDL_Renderer *renderer, float delta_time);
void Game_Input(const SDL_Event *event);
void Game_Release();

void Game_SetState(GameState state);

GameState Game_GetState();

#endif
