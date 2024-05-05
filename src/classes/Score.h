#ifndef __SCORE_H__
#define __SCORE_H__

#include <Engine.h>
#include <GameObjects.h>

static struct _score_prototype_ {
	uint64_t score;			// r
	uint64_t best_score;	// r
	bool show_best_score;	// r
	bool redraw_score;		// r
} Score;

void Score_Create();
void Score_Increment();
void Score_Restart();

uint64_t Score_GetScoreForDraw();
uint64_t Score_GetBestScore();
bool Score_DrawBestScore();
bool Score_RedrawScore();

#endif
