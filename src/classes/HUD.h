#ifndef __HUD_H__
#define __HUD_H__

#include <Engine.h>
#include <GameObjects.h>

static struct _hud_prototype_ {
	Image *title;
	Image *label_play;
	Image *label_score;
	Image *label_best;

	BitmapFont *font_numbers;
	BitmapText *text_score;
	BitmapText *text_best;

	float blink_time;
	float time_to_blink;
} HUD;

void HUD_Create();
void HUD_Update(SDL_Renderer *renderer, float delta_time);
void HUD_Release();

#endif
