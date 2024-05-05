#include "Player.h"
#include "Bullets.h"
#include "../Global.h"
#include "../Game.h"

#include "Enemies.h"

#define ARROW_KEYS(k)   (k == SDLK_LEFT || k == SDLK_RIGHT || k == SDLK_UP || k == SDLK_DOWN)

// Private
void Player_Shoot() {
    // Check if the shoot delay has ended
    if (Player.fire_charged) {
        // Restart the shoot delay
        Player.fire_charged = false;
        Player.fire_charging_time = 0;

        // Shoot a bullet and play its sound
        Bullets_Shoot(PLAYER_BULLET, Sprite_GetBody(SPRITE(Player.sprite)));
        SoundManager_Play("player shoot", SOUND_EFFECTS_VOLUME, false);
    }
}

// Private
void Player_InitialState() {
    // Restart the destroy system
    Player.is_death = false;
    Player.time_to_delete = 0;
    Player.can_restart = false;

    // Allow to shoot when respawn
    Player.fire_charged = true;

    // Start the respawn system
    Player.respawning = true;
    Player.respawn_time_left = PLAYER_RESPAWN_TIME;
    Player.respawn_blink_time = PLAYER_RESPAWN_BLINK_TIME;
    Sprite_SetCollisionsEnabled(SPRITE(Player.sprite), false);

    // Restart the player position to its default initial
    Sprite_SetPosition(SPRITE(Player.sprite), PLAYER_START_X, PLAYER_START_Y);

    // Restart the player animation
    AnimatedSprite_SetAnimation(Player.sprite, Player.animations.idle);
}

void Player_Create() {
    // Create the player animations
    Player.animations.move = Animation_New(2, "player idle 1", "player idle 2");
    Player.animations.idle = Animation_New(1, "player");
    Player.animations.explosion = Animation_New(4, "explode 1", "explode 2", "explode 3", "explode 4");

    // Setup the player animations
    Animation_SetDurationPerFrame(Player.animations.move, PLAYER_FRAME_DURATION);
    Animation_SetDurationPerFrame(Player.animations.explosion, EXPLOSION_FRAME_DURATION);

    // Create the animated sprite
    Player.sprite = AnimatedSprite_New();

    // Set the world limit
    Sprite_SetWorldBounds(SPRITE(Player.sprite), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    Sprite_SetWorldBoundsOn(SPRITE(Player.sprite), true);

    // Adjust the box size for better collisions
    Sprite_SetBoxSize(SPRITE(Player.sprite), PLAYER_WIDTH, PLAYER_HEIGHT);
    Sprite_SetBoxOffsetY(SPRITE(Player.sprite), PLAYER_OFFSET_Y);

    // Set to the initial state
    Player_InitialState();
}

void Player_Input(const SDL_Event* e) {
    // Don't process the player input if the player is death
    // in other words this means that the explotion animation is playing
    if (Player.is_death) return;

    switch (e->type) {
        case SDL_KEYDOWN: {
            switch (e->key.keysym.sym) {
                // Moves to left, right, up, or down
                case SDLK_LEFT:
                    Sprite_SetVelocityX(SPRITE(Player.sprite), -PLAYER_VELOCITY);
                    break;
                case SDLK_RIGHT:
                    Sprite_SetVelocityX(SPRITE(Player.sprite), PLAYER_VELOCITY);
                    break;
                case SDLK_UP:
                    Sprite_SetVelocityY(SPRITE(Player.sprite), -PLAYER_VELOCITY);
                    break;
                case SDLK_DOWN:
                    Sprite_SetVelocityY(SPRITE(Player.sprite), PLAYER_VELOCITY);
                    break;
                // Query the shoot syste
                case SDLK_SPACE:
                    Player_Shoot();
                    break;
            }

            // If moving set the move animation
            if (ARROW_KEYS(e->key.keysym.sym)) {
                AnimatedSprite_SetAnimation(Player.sprite, Player.animations.move);
            }

            break;
        }
        case SDL_KEYUP: {
            // Cancel any move and set the idle animation
            if (ARROW_KEYS(e->key.keysym.sym)) {
                Sprite_SetVelocityX(SPRITE(Player.sprite), 0);
                Sprite_SetVelocityY(SPRITE(Player.sprite), 0);

                AnimatedSprite_SetAnimation(Player.sprite, Player.animations.idle);
            }
            break;
        }
    }

}

void Player_Update(SDL_Renderer *renderer, float delta_time) {
    AnimatedSprite_Draw(Player.sprite, renderer);

    // Update the respawning system
    if (Player.respawning) {
        Player.respawn_time_left -= delta_time;

        // If the respawn time ends enable the collisions
        // and set the player visible
        if (Player.respawn_time_left <= 0) {
            Player.respawning = false;
            Sprite_SetCollisionsEnabled(SPRITE(Player.sprite), true);
            Sprite_SetVisible(SPRITE(Player.sprite), true);
        }
        // Else indicate that the player is temporarily invincible
        else {
            Player.respawn_blink_time -= delta_time;

            if (Player.respawn_blink_time <= 0) {
                Player.respawn_blink_time = PLAYER_RESPAWN_BLINK_TIME;
                Sprite_SetVisible(SPRITE(Player.sprite), !Sprite_IsVisible(SPRITE(Player.sprite)));
            }
        }
    }

    // Update the destroy system if the player was impacted before
    if (Player.is_death) {
        Player.time_to_delete -= delta_time;

        // Check if the explotion animation has ended
        if (Player.time_to_delete <= 0) {
            // If it is hide the player and show the game over screen
            Player.can_restart = true;
            Sprite_SetVisible(SPRITE(Player.sprite), false);
            Game_SetState(GAME_STATE_RESTART);
        }
    }
    // If the player isn't dead update the physics and the shoot system
    else {
        Sprite_Update(SPRITE(Player.sprite), delta_time);

        // Update the shoot system
        if (!Player.fire_charged) {
            Player.fire_charging_time += delta_time;

            // Check if the shoot delay has ended
            if (Player.fire_charging_time >= PLAYER_FIRE_RELOAD_TIME) {
                Player.fire_charged = true;
                Player.fire_charging_time = 0;
            }
        }
    }
}

void Player_Release() {
    AnimatedSprite_Destroy(Player.sprite);
    Animation_Destroy(Player.animations.move);
    Animation_Destroy(Player.animations.idle);
    Animation_Destroy(Player.animations.explosion);
}

bool Player_CollisionWith(PhysicsBody *collider) {
    PhysicsBody *target = Sprite_GetBody(SPRITE(Player.sprite));
    return PhysicsBody_CollisionWith(target, collider);
}

void Player_EnemyCollision() {
    PhysicsBody *target = Sprite_GetBody(SPRITE(Player.sprite));
    if (Enemies_CollisionWith(target) != -1) {
        Player_WasImpacted();
    }
}

void Player_WasImpacted() {
    // Disable the collitions to show the explotion animation
    Sprite_SetCollisionsEnabled(SPRITE(Player.sprite), false);

    // Play the explotion animation and its sound
    AnimatedSprite_SetAnimation(Player.sprite, Player.animations.explosion);
    SoundManager_Play("player die", SOUND_EFFECTS_VOLUME, false);

    // Start the destroy system
    Player.time_to_delete = TIME_TO_DELETE;
    Player.is_death = true;

    // Cancel any movement
    Sprite_SetVelocityX(SPRITE(Player.sprite), 0);
    Sprite_SetVelocityY(SPRITE(Player.sprite), 0);
}

void Player_Restart() {
    Player_InitialState();
    Sprite_SetVisible(SPRITE(Player.sprite), true);
}
