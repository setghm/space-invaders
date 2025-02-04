/*
 * Game engine configuration file
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#define PIXELS(pixels)							(pixels * DEFAULT_SCALE)
#define PIXELS_PER_SECOND(pps)					(pps * DEFAULT_SCALE)

// Engine Configuration

#define ASSETS_DIRECTORY						"assets"
#define DEFAULT_SCALE							5
#define WINDOW_WIDTH							PIXELS(128)
#define WINDOW_HEIGHT							PIXELS(96)

// Game Objects Configuration

#define DEFAULT_ORIGIN_X                        0.5f
#define DEFAULT_ORIGIN_Y                        0.5f

#define IMAGE_DEFAULT_SCALE                     1
#define IMAGE_DEFAULT_VISIBILITY                true
#define SPRITE_COLLISIONS_ENABLED_BY_DEFAULT    true
#define SOLID_DEFAULT_ALPHA                     255
#define SOLID_DEFAULT_VISIBILITY                true
#define SOLID_COLLISIONS_ENABLED_BY_DEFAULT     true

#define PHYSICS_BODY_DEFAULT_DRAW_RED           224
#define PHYSICS_BODY_DEFAULT_DRAW_GREEN         41
#define PHYSICS_BODY_DEFAULT_DRAW_BLUE          20
#define PHYSICS_BODY_DEFAULT_FILL_ALPHA         200
#define PHYSICS_BODY_DEFAULT_STROKE_ALPHA       100

#define ANIMATION_FRAME_DURATION(frame_count)	(frame_count / 24.0f)

#define BITMAP_TEXT_DEFAULT_POINT_SIZE          12
#define FONT_WHITESPACE_WIDTH(points)			(points * POINTS_IN_PIXELS / 1.5f)
#define FONT_CHAR_SPACING(points)               (points * POINTS_IN_PIXELS / 3.0f)
#define POINTS_IN_PIXELS						(4.0f/3.0f)

#endif
