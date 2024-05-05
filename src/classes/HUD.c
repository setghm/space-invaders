#include "HUD.h"
#include "Score.h"
#include "../Game.h"
#include "../Global.h"

void HUD_Create() {
	// Set the default blink time (in seconds)
	HUD.blink_time = 0.5f;

	// Create the bitmap font for display the score
	HUD.font_numbers = BitmapFont_New();

	BitmapFont_AddCharacter(HUD.font_numbers, "zero", '0');
	BitmapFont_AddCharacter(HUD.font_numbers, "one", '1');
	BitmapFont_AddCharacter(HUD.font_numbers, "two", '2');
	BitmapFont_AddCharacter(HUD.font_numbers, "three", '3');
	BitmapFont_AddCharacter(HUD.font_numbers, "four", '4');
	BitmapFont_AddCharacter(HUD.font_numbers, "five", '5');
	BitmapFont_AddCharacter(HUD.font_numbers, "six", '6');
	BitmapFont_AddCharacter(HUD.font_numbers, "seven", '7');
	BitmapFont_AddCharacter(HUD.font_numbers, "eight", '8');
	BitmapFont_AddCharacter(HUD.font_numbers, "nine", '9');

	// Create the bitmap text
	HUD.text_score = BitmapText_New(HUD.font_numbers, "0");
	HUD.text_best = BitmapText_New(HUD.font_numbers, "0");

	// Create the labels
	HUD.label_score = Image_New("score");
	Image_SetScale(HUD.label_score, LABEL_DEFAULT_SCALE);
	Image_SetOrigin(HUD.label_score, 0, 0);

	HUD.label_best = Image_New("best");
	Image_SetScale(HUD.label_best, LABEL_DEFAULT_SCALE);
	Image_SetOrigin(HUD.label_best, 0, 0);

	HUD.label_play = Image_New("play");

	// Create the title
	HUD.title = Image_New("title");

	// Set the position for the score indicator
	Image_SetPosition(HUD.label_score, SCORE_TEXT_X_POSITION, SCORE_TEXT_Y_POSITION);
	BitmapText_SetPosition(HUD.text_score, SCORE_TEXT_X_POSITION + Image_GetX(HUD.label_score) + Image_GetDisplayWidth(HUD.label_score), SCORE_TEXT_Y_POSITION);
}

void HUD_Release() {
	BitmapFont_Destroy(HUD.font_numbers);
	BitmapText_Destroy(HUD.text_score);
	BitmapText_Destroy(HUD.text_best);
	Image_Destroy(HUD.label_score);
	Image_Destroy(HUD.label_best);
	Image_Destroy(HUD.label_play);
	Image_Destroy(HUD.title);
}

// Private
void HUD_UpdateStateInitial(SDL_Renderer *renderer, float delta_time) {
	// Make the play label blink
	HUD.time_to_blink -= delta_time;

	if (HUD.time_to_blink <= 0) {
		HUD.time_to_blink = HUD.blink_time;
		Image_SetVisible(HUD.label_play, !Image_IsVisible(HUD.label_play));
	}

	// Draw the HUD classes
	Image_Draw(HUD.label_play, renderer);
	Image_Draw(HUD.title, renderer);
}

// Private
void HUD_UpdateStatePlaying(SDL_Renderer *renderer) {
	if (Score_RedrawScore()) {
		char score_str[20] = {0};
		uint64_t score = Score_GetScoreForDraw();

		sprintf(score_str, "%lu", score);

		BitmapText_SetText(HUD.text_score, score_str);
	}

	if (Score_DrawBestScore()) {
		Image_Draw(HUD.label_best, renderer);
		BitmapText_Draw(HUD.text_best, renderer);
	}

	Image_Draw(HUD.label_score, renderer);
	BitmapText_Draw(HUD.text_score, renderer);
}

// Private
void HUD_UpdateStateRestart(SDL_Renderer *renderer, float delta_time) {
	HUD_UpdateStateInitial(renderer, delta_time);

	if (Score_DrawBestScore()) {
		Image_Draw(HUD.label_best, renderer);
		BitmapText_Draw(HUD.text_best, renderer);
	}
}

void HUD_Update(SDL_Renderer *renderer, float delta_time) {
	switch (Game_GetState()) {
		case GAME_STATE_INITIAL:
			HUD_UpdateStateInitial(renderer, delta_time);
			break;
		case GAME_STATE_PLAYING:
			HUD_UpdateStatePlaying(renderer);
			break;
		case GAME_STATE_RESTART:
			HUD_UpdateStateRestart(renderer, delta_time);
			break;
	}
}

// Private
void HUD_GameStateChanged(GameState state) {
	switch (state) {
		case GAME_STATE_INITIAL: {
			// Restart the blink time
			HUD.time_to_blink = HUD.blink_time;

			// Set the initial position for the game title and the play label
			Image_SetPosition(HUD.title, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2/5);
			Image_SetPosition(HUD.label_play, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/5);
			break;
		}
		case GAME_STATE_PLAYING: {
			// Hide the game title and the play label
			Image_SetVisible(HUD.title, false);
			Image_SetVisible(HUD.label_play, false);

			// Show the score indicator and the best score indicator
			BitmapText_SetVisible(HUD.text_score, true);
			Image_SetVisible(HUD.label_score, true);

			// Reposition the best score indicator
			BitmapText_SetPosition(HUD.text_best, WINDOW_WIDTH - (10 + BitmapText_GetDisplayWidth(HUD.text_best)), 10);
			Image_SetPosition(HUD.label_best, BitmapText_GetX(HUD.text_best) - (10 + Image_GetDisplayWidth(HUD.label_best)), 10);
			break;
		}
		case GAME_STATE_RESTART: {
			// Restart the blink time
			HUD.time_to_blink = HUD.blink_time;

			// Show the game title and the play label
			Image_SetVisible(HUD.title, true);
			Image_SetVisible(HUD.label_play, true);

			// Show the best score indicator
			if (Score_DrawBestScore()) {
				// Reposition the game title and the play label
				Image_SetPosition(HUD.title, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 1/4);
				Image_SetPosition(HUD.label_play, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/4);

				// Get the best score and display as bitmap text
				char best_score_str[20] = {0};
				uint64_t best_score = Score_GetBestScore();

				sprintf(best_score_str, "%lu", best_score);

				BitmapText_SetText(HUD.text_best, best_score_str);

				// Reposition the best score indicator
				float indicator_width = BitmapText_GetDisplayWidth(HUD.text_best) + Image_GetDisplayWidth(HUD.label_best) + SCORE_TEXT_SPACING;

				int indicator_x = (WINDOW_WIDTH - indicator_width) / 2;
				int indicator_y = WINDOW_HEIGHT * 0.5f;

				Image_SetPosition(HUD.label_best, indicator_x, indicator_y);
				BitmapText_SetPosition(HUD.text_best, indicator_x + 10 + Image_GetDisplayWidth(HUD.label_best), indicator_y);
			} else {
				// Set the initial position for the game title and the play label
				Image_SetPosition(HUD.title, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2/5);
				Image_SetPosition(HUD.label_play, WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/5);
			}
			break;
		}
	}
}
