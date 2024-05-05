#include "Game.h"

#include "classes/Player.h"
#include "classes/Enemies.h"
#include "classes/Bullets.h"
#include "classes/Score.h"
#include "classes/HUD.h"

#include "Global.h"

void HUD_GameStateChanged(GameState state);

void Game_Preload() {
	// Preload all the texture assets
	TextureManager_Load("enemy 1", "enemy0.png");
	TextureManager_Load("enemy 2", "enemy1.png");
	TextureManager_Load("player", "player0.png");
	TextureManager_Load("player idle 1", "player1.png");
	TextureManager_Load("player idle 2", "player2.png");
	TextureManager_Load("explode 1", "explode0.png");
	TextureManager_Load("explode 2", "explode1.png");
	TextureManager_Load("explode 3", "explode2.png");
	TextureManager_Load("explode 4", "explode3.png");
	TextureManager_Load("best", "best.png");
	TextureManager_Load("score", "score.png");
	TextureManager_Load("title", "title.png");
	TextureManager_Load("play", "press to play.png");
	TextureManager_Load("zero", "zero.png");
	TextureManager_Load("one", "one.png");
	TextureManager_Load("two", "two.png");
	TextureManager_Load("three", "three.png");
	TextureManager_Load("four", "four.png");
	TextureManager_Load("five", "five.png");
	TextureManager_Load("six", "six.png");
	TextureManager_Load("seven", "seven.png");
	TextureManager_Load("eight", "eight.png");
	TextureManager_Load("nine", "nine.png");

	// Preload all the sounds
	SoundManager_Load("bg music", "main.ogg");
	SoundManager_Load("start", "start.ogg");
	SoundManager_Load("player shoot", "player_shoot.ogg");
	SoundManager_Load("player die", "player_explotion.ogg");
	SoundManager_Load("enemy shoot", "enemy_shoot.ogg");
	SoundManager_Load("enemy die", "enemy_explotion.ogg");
}

void Game_Create() {
	// Create all the components
	Player_Create();
	Enemies_Create();
	HUD_Create();

	// Reproduce the background music in loop
	SoundManager_Play("bg music", BACKGROUND_MUSIC_VOLUME, true);

	// Set the initial state
	Game_SetState(GAME_STATE_INITIAL);
}

void Game_Update(SDL_Renderer *renderer, float delta_time) {
	Enemies_Update(renderer, delta_time);
	Bullets_Update(renderer, delta_time);

	if (Game.state == GAME_STATE_PLAYING) {
		Player_Update(renderer, delta_time);

		// Check collisions
		Player_EnemyCollision();
		Bullets_PlayerBulletEnemyCollision();
		Bullets_EnemyBulletPlayerCollision();
	}

	// Draw last = Draw above all
	HUD_Update(renderer, delta_time);
}

// Private
bool Game_PressToPlay(const SDL_Event *event) {
	// Return true if any key or button is pressed
	return	event->type == SDL_KEYDOWN ||
			event->type == SDL_CONTROLLERBUTTONDOWN ||
			event->type == SDL_FINGERDOWN ||
			event->type == SDL_JOYBUTTONDOWN ||
			event->type == SDL_MOUSEBUTTONDOWN;
}

void Game_Input(const SDL_Event *event) {
	if (Game.state == GAME_STATE_PLAYING) {
		// Process the player input if playing
		Player_Input(event);
	} else {
		// Check for any key or button pressed to start playing
		if (Game_PressToPlay(event)) {
			Game_SetState(GAME_STATE_PLAYING);
		}
	}
}

void Game_Release() {
	// Call release method from all components
	Player_Release();
	Enemies_Release();
	Bullets_Release();
	HUD_Release();
}

void Game_SetState(GameState state) {
	// Change the game state and notify the HUD
	Game.state = state;

	// Restart score if the state is restart
	if (state == GAME_STATE_RESTART) {
		Score_Restart();
	}
	// if the game will start restart the player to its initial state
	else if (state == GAME_STATE_PLAYING) {
		SoundManager_Play("start", SOUND_EFFECTS_VOLUME, false);
		Player_Restart();
	}

	HUD_GameStateChanged(state);
}

GameState Game_GetState() {
	return Game.state;
}
