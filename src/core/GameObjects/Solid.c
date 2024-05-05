#include "Solid.h"

#include <stdlib.h>
#include <string.h>

#include <Config.h>

Solid *Solid_New(float width, float height) {
	Solid *solid = (Solid *) malloc(sizeof(Solid));
	memset(solid, 0, sizeof(Solid));

	solid->color.a = SOLID_DEFAULT_ALPHA;
	Solid_SetSize(solid, width, height);
    solid->visible = SOLID_DEFAULT_VISIBILITY;
    solid->body.collisions_enabled = SOLID_COLLISIONS_ENABLED_BY_DEFAULT;

	return solid;
}

void Solid_Draw(Solid *solid, SDL_Renderer *renderer) {
    if (solid->visible) {
		uint8_t save_r, save_g, save_b, save_a;

		SDL_Rect box = {
            (int) roundf(solid->body.box.x),
            (int) roundf(solid->body.box.y),
            (int) roundf(solid->body.box.w),
            (int) roundf(solid->body.box.h)
		};

		// Save the original draw color
		SDL_GetRenderDrawColor(renderer, &save_r, &save_g, &save_b, &save_a);

		// Draw a filled rectangle
		SDL_SetRenderDrawColor(renderer, solid->color.r, solid->color.g, solid->color.b, solid->color.a);
		SDL_RenderFillRect(renderer, &box);

		// Restore the original draw color
		SDL_SetRenderDrawColor(renderer, save_r, save_g, save_b, save_a);
	}
#ifdef DEBUG_PHYSICS
	PhysicsBody_DebugDraw(&solid->body, renderer);
#endif
}

inline void Solid_Update(Solid *solid, float delta_time) {
    PhysicsBody_Update(&solid->body, delta_time);
}

inline void Solid_Destroy(Solid *solid) {
	free(solid);
}


inline bool Solid_CollisionWithArea(Solid *solid, SDL_Rect *area) {
	return PhysicsBody_CollisionWithArea(&solid->body, area);
}

// Setters

inline void Solid_SetPosition(Solid *solid, float x, float y) {
	solid->body.box.x = x;
	solid->body.box.y = y;
}

inline void Solid_SetSize(Solid *solid, float width, float height) {
	solid->body.box.w = width;
	solid->body.box.h = height;
}

inline void Solid_SetColor(Solid *solid, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	solid->color.r = r;
	solid->color.g = g;
	solid->color.b = b;
	solid->color.a = a;
}

inline void Solid_SetVelocityX(Solid *solid, float vx) {
	PhysicsBody_SetVelocityX(&solid->body, vx);
}

inline void Solid_SetVelocityY(Solid *solid, float vy) {
	PhysicsBody_SetVelocityY(&solid->body, vy);
}

inline void Solid_SetVisible(Solid *solid, bool visible) {
    solid->visible = visible;
}

inline void Solid_SetCollisionsEnabled(Solid *solid, bool enabled) {
    solid->body.collisions_enabled = enabled;
}

// Getters

inline float Solid_GetX(Solid *solid) {
	return solid->body.box.x;
}

inline float Solid_GetY(Solid *solid) {
	return solid->body.box.y;
}

inline float Solid_GetWidth(Solid *solid) {
	return solid->body.box.w;
}

inline float Solid_GetHeight(Solid *solid) {
	return solid->body.box.h;
}
