#include "Score.h"

void Score_Create() {
	Score.best_score = 0;
	Score.score = 0;
	Score.show_best_score = false;
	Score.redraw_score = true;
}

void Score_Increment() {
	Score.score++;
	Score.redraw_score = true;
}

void Score_Restart() {
	if (Score.score > Score.best_score) {
		Score.show_best_score = true;
		Score.best_score = Score.score;
	}

	Score.score = 0;
	Score.redraw_score = true;
}

uint64_t Score_GetScoreForDraw() {
	Score.redraw_score = false;
	return Score.score;
}

uint64_t Score_GetBestScore() {
	return Score.best_score;
}

bool Score_DrawBestScore() {
	return Score.show_best_score;
}

bool Score_RedrawScore() {
	return Score.redraw_score;
}
