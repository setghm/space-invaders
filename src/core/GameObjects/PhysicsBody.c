#include "PhysicsBody.h"

#include <math.h>

#include <Config.h>

// Private
void PhysicsBody_ApplyVelocityX(PhysicsBody *body, float delta_time) {
    if (body->velocity.x == 0) return;

    float apply_velocity = body->velocity.x * delta_time;

    if (body->world_bounds_on) {
        float distance = (float) abs((int) body->velocity.x);
        float xx = body->box.x + body->box_offset.x; // Left x
        float xw = xx + body->box.w; // Right x

        if (body->velocity.x < 0) {
            distance = xx - body->world_bounds.x;

            if (xx <= body->world_bounds.x) {
                return;
            }
        }
        else if (body->velocity.x > 0) {
            distance = body->world_bounds.w - xw;

            if (xw >= body->world_bounds.w) {
                return;
            }
        }

        body->box.x += ((float) abs((int) apply_velocity) > distance) ? distance : apply_velocity;
        return;
    }

    body->box.x += apply_velocity;
}

// Private
void PhysicsBody_ApplyVelocityY(PhysicsBody *body, float delta_time) {
    if (body->velocity.y == 0) return;

    float apply_velocity = body->velocity.y * delta_time;

    if (body->world_bounds_on) {
        float distance = (float) abs((int) body->velocity.y);
        float yy = body->box.y + body->box_offset.y; // Top y
        float yh = yy + body->box.h; // Bottom y

        if (body->velocity.y < 0) {
            distance = yy - body->world_bounds.y;

            if (yy <= body->world_bounds.y) {
                return;
            }
        }
        else if (body->velocity.y > 0) {
            distance = body->world_bounds.h - yh;

            if (yh >= body->world_bounds.h) {
                return;
            }
        }

        body->box.y += ((float) abs((int) apply_velocity) > distance) ? distance : apply_velocity;
        return;
    }

    body->box.y += apply_velocity;
}

bool PhysicsBody_CollisionWith(PhysicsBody *target, PhysicsBody *collider) {
    if (!target->collisions_enabled || !collider->collisions_enabled)
        return false;

    float ax1 = target->box.x + target->box_offset.x,
        ay1 = target->box.y + target->box_offset.y,
        ax2 = ax1 + target->box.w,
        ay2 = ay1 + target->box.h,
        bx1 = collider->box.x + collider->box_offset.x,
        by1 = collider->box.y + collider->box_offset.y,
        bx2 = bx1 + collider->box.w,
        by2 = by1 + collider->box.h;

    return  (ax1 >= bx1 || ax2 >= bx1) && (ax1 <= bx2 || ax2 <= bx2) &&
            (ay1 >= by1 || ay2 >= by1) && (ay1 <= by2 || ay2 <= by2);
}

bool PhysicsBody_CollisionWithArea(PhysicsBody *target, SDL_Rect *area) {
    if (!target->collisions_enabled)
        return false;

    float ax1 = target->box.x + target->box_offset.x,
          ay1 = target->box.y + target->box_offset.y,
          ax2 = ax1 + target->box.w,
          ay2 = ay1 + target->box.h,
          bx1 = (float) area->x,
          by1 = (float) area->y,
          bx2 = bx1 + (float) area->w,
          by2 = by1 + (float) area->h;

    return  (ax1 >= bx1 || ax2 >= bx1) && (ax1 <= bx2 || ax2 <= bx2) &&
            (ay1 >= by1 || ay2 >= by1) && (ay1 <= by2 || ay2 <= by2);
}

inline void PhysicsBody_Update(PhysicsBody *body, float delta_time) {
    PhysicsBody_ApplyVelocityX(body, delta_time);
    PhysicsBody_ApplyVelocityY(body, delta_time);
}

void PhysicsBody_DebugDraw(PhysicsBody *body, SDL_Renderer *renderer) {
    if (!body->collisions_enabled)
        return;

    uint8_t save_r, save_g, save_b, save_a;
    SDL_Rect t_body = {
        (int) roundf(body->box.x + body->box_offset.x),
        (int) roundf(body->box.y + body->box_offset.y),
        (int) roundf(body->box.w),
        (int) roundf(body->box.h)
    };

    // Save the original draw color
    SDL_GetRenderDrawColor(renderer, &save_r, &save_g, &save_b, &save_a);

    // Draw the border
    SDL_SetRenderDrawColor(renderer,
                           PHYSICS_BODY_DEFAULT_DRAW_RED,
                           PHYSICS_BODY_DEFAULT_DRAW_GREEN,
                           PHYSICS_BODY_DEFAULT_DRAW_BLUE,
                           PHYSICS_BODY_DEFAULT_STROKE_ALPHA);
    SDL_RenderDrawRect(renderer, &t_body);

    // Draw the fill of the rectangle
    SDL_SetRenderDrawColor(renderer,
                           PHYSICS_BODY_DEFAULT_DRAW_RED,
                           PHYSICS_BODY_DEFAULT_DRAW_GREEN,
                           PHYSICS_BODY_DEFAULT_DRAW_BLUE,
                           PHYSICS_BODY_DEFAULT_FILL_ALPHA);
    SDL_RenderFillRect(renderer, &t_body);

    // Restore the original draw color
    SDL_SetRenderDrawColor(renderer, save_r, save_g, save_b, save_a);
}

// Setters

inline void PhysicsBody_SetBoxSize(PhysicsBody *body, float w, float h) {
    body->box.w = w;
    body->box.h = h;
}

inline void PhysicsBody_SetBoxOffsetX(PhysicsBody *body, float x) {
    body->box_offset.x = x;
}

inline void PhysicsBody_SetBoxOffsetY(PhysicsBody *body, float y) {
    body->box_offset.y = y;
}

inline void PhysicsBody_SetX(PhysicsBody *body, float x) {
    body->box.x = x;
}

inline void PhysicsBody_SetY(PhysicsBody *body, float y) {
    body->box.y = y;
}

inline void PhysicsBody_SetVelocityX(PhysicsBody *body, float x) {
    body->velocity.x = x;
}

inline void PhysicsBody_SetVelocityY(PhysicsBody *body, float y) {
    body->velocity.y = y;
}

inline void PhysicsBody_SetWorldBounds(PhysicsBody *body, float x1, float y1, float x2, float y2) {
    body->world_bounds.x = x1;
    body->world_bounds.y = y1;
    body->world_bounds.w = x2;
    body->world_bounds.h = y2;
}

inline void PhysicsBody_SetWorldBoundsOn(PhysicsBody *body, bool turnon) {
    body->world_bounds_on = turnon;
}

inline void PhysicsBody_SetScale(PhysicsBody *body, float scale) {
    body->box.w *= scale;
    body->box.h *= scale;
}

inline void PhysicsBody_SetCollisionsEnabled(PhysicsBody *body, bool enabled) {
    body->collisions_enabled = enabled;
}

// Getters

inline float PhysicsBody_GetBoxOffsetX(PhysicsBody *body) {
    return body->box_offset.x;
}

inline float PhysicsBody_GetBoxOffsetY(PhysicsBody *body) {
    return body->box_offset.y;
}

inline float PhysicsBody_GetX(PhysicsBody *body) {
    return body->box.x;
}

inline float PhysicsBody_GetY(PhysicsBody *body) {
    return body->box.y;
}

inline float PhysicsBody_GetVelocityX(PhysicsBody *body) {
    return body->velocity.x;
}

inline float PhysicsBody_GetVelocityY(PhysicsBody *body) {
    return body->velocity.y;
}

