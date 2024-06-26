#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Config.h>

static const char*
	GAME_TITLE = "Space Invaders";

static const int
	PLAYER_START_X = WINDOW_WIDTH / 2,
	PLAYER_START_Y = WINDOW_HEIGHT * 0.75,
	PLAYER_VELOCITY = PIXELS_PER_SECOND(110),
	PLAYER_BULLET_WIDTH = PIXELS(1),
	PLAYER_BULLET_HEIGHT = PIXELS(4),
	PLAYER_BULLET_VELOCITY = PIXELS_PER_SECOND(-300),
	PLAYER_BULLET_0_X = PIXELS(1),
	PLAYER_BULLET_0_Y = PIXELS(2),
	PLAYER_BULLET_1_X = PIXELS(10),
	PLAYER_BULLET_1_Y = PIXELS(2),
	PLAYER_WIDTH = PIXELS(12),
	PLAYER_HEIGHT = PIXELS(10),
	PLAYER_OFFSET_Y = PIXELS(2);

static const int
	ENEMY_HEIGHT = PIXELS(10),
	ENEMY_WIDTH = PIXELS(10),
	ENEMY_BULLET_WIDTH = PIXELS(2),
	ENEMY_BULLET_HEIGHT = PIXELS(4),
	ENEMY_BULLET_VELOCITY_MIN = PIXELS_PER_SECOND(80),
    ENEMY_BULLET_VELOCITY_MAX = PIXELS_PER_SECOND(160),
	ENEMY_BULLET_X = PIXELS(5),
	ENEMY_BULLET_Y = PIXELS(9),
	ENEMY_OFFSET_X = PIXELS(1),
	ENEMY_OFFSET_Y = PIXELS(3);

static const int
	ENEMIES_IN_ROW = 7,
	ENEMIES_ENTRANCE_VELOCITY = PIXELS_PER_SECOND(50),
    ENEMIES_ATTACK_MIN_VELOCITY = PIXELS_PER_SECOND(40),
	ENEMIES_ATTACK_MAX_VELOCITY = PIXELS_PER_SECOND(80),
	ENEMIES_MARGIN_HORIZONTAL = PIXELS(16),
	ENEMIES_MARGIN_VERTICAL = PIXELS(4),
	ENEMIES_SPACE_BETWEEN_X = PIXELS(6),
	ENEMIES_SPACE_BETWEEN_Y = PIXELS(2),
	ENEMIES_ATTACK_MIN_ROWS = 2,
	ENEMIES_ATTACK_MAX_ROWS = 4,
	ENEMIES_ATTACK_MIN_X = ENEMIES_MARGIN_HORIZONTAL,
	ENEMIES_ATTACK_MAX_X = WINDOW_WIDTH - ENEMIES_MARGIN_HORIZONTAL,
	ENEMIES_ATTACK_MIN_Y = ENEMIES_MARGIN_VERTICAL,
	ENEMIES_ATTACK_MAX_Y = (int) (WINDOW_HEIGHT / 2),
	ENEMIES_ATTACK_START_X = -ENEMY_WIDTH,
	ENEMIES_ATTACK_START_Y = -ENEMY_HEIGHT,
	ENEMIES_TARGET_X = WINDOW_WIDTH + ENEMY_WIDTH,
	ENEMIES_TARGET_Y = WINDOW_HEIGHT + ENEMY_HEIGHT,
	ENEMIES_ATTACK_X_ZONE_0 = 0,
    ENEMIES_ATTACK_X_ZONE_1 = WINDOW_WIDTH / 3,
    ENEMIES_ATTACK_X_ZONE_2 = WINDOW_WIDTH / 3 * 2,
    ENEMIES_ATTACK_X_ZONE_3 = WINDOW_WIDTH,
    ENEMIES_ATTACK_Y_ZONE_1 = ENEMIES_ATTACK_MAX_Y / 3,
    ENEMIES_ATTACK_Y_ZONE_2 = ENEMIES_ATTACK_MAX_Y / 3 * 2,
    ENEMIES_ATTACK_Y_ZONE_3 = ENEMIES_ATTACK_MAX_Y;

// Durations in seconds
static const float
	PLAYER_FRAME_DURATION = 0.1f,
	PLAYER_RESPAWN_TIME = 3,
	PLAYER_RESPAWN_BLINK_TIME = 0.1f,
	ENEMY_FRAME_DURATION = 0.5f,
	EXPLOSION_FRAME_DURATION = 0.1f,
	TIME_TO_DELETE = 0.4f,
	PLAYER_FIRE_RELOAD_TIME = 0.2f,
	ENEMIES_TIME_GEN_MIN = 0.5f,
	ENEMIES_TIME_GEN_MAX = 1.5f,
	ENEMIES_ATTACK_MIN_TIME = 20.0f,
	ENEMIES_ATTACK_MAX_TIME = 40.0f,
	ENEMY_FIRE_MIN_TIME = 0.5f,
	ENEMY_FIRE_MAX_TIME = 8.0f,
	ENEMIES_REGENERATING_TIME = 1.0f,
	GROUP_ATTACK_FIRE_MIN_TIME = 4.0f,
	GROUP_ATTACK_FIRE_MAX_TIME = 8.0f;

// UI constants
static const float
	SCORE_TEXT_X_POSITION = PIXELS(2),
	SCORE_TEXT_Y_POSITION = PIXELS(2),
	SCORE_TEXT_SPACING = PIXELS(2),
	LABEL_DEFAULT_SCALE = 0.48f * POINTS_IN_PIXELS;

// Audio constants
static const int
	BACKGROUND_MUSIC_VOLUME = 25,
	SOUND_EFFECTS_VOLUME = 50;

#endif
