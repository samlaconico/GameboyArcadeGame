#include "player.h"
#include "raymath.h"
#include "math.h"

const Rectangle walk_down[] = {(Rectangle){32, 16, 16, 16}, (Rectangle){16, 16, 16, 16}, (Rectangle){48, 16, 16, 16}, (Rectangle){16, 16, 16, 16}};
const Rectangle walk_up[] = {(Rectangle){32, 0, 16, 16}, (Rectangle){16, 0, 16, 16}, (Rectangle){48, 0, 16, 16}, (Rectangle){16, 0, 16, 16}};
const Rectangle walk_right[] = {(Rectangle){16, 32, 16, 16}, (Rectangle){0, 32, 16, 16}, (Rectangle){16, 32, 16, 16}, (Rectangle){0, 32, 16, 16}};
const Rectangle walk_left[] = {(Rectangle){16, 48, 16, 16}, (Rectangle){0, 48, 16, 16}, (Rectangle){16, 48, 16, 16}, (Rectangle){0, 48, 16, 16}};
const Rectangle idle_left[] = {(Rectangle){0, 48, 16, 16}, (Rectangle){0, 48, 16, 16}, (Rectangle){0, 48, 16, 16}, (Rectangle){0, 48, 16, 16}};
const Rectangle idle_right[] = {(Rectangle){0, 32, 16, 16}, (Rectangle){0, 32, 16, 16}, (Rectangle){0, 32, 16, 16}, (Rectangle){0, 32, 16, 16}};
const Rectangle idle_up[] = {(Rectangle){0, 0, 16, 16}, (Rectangle){0, 0, 16, 16}, (Rectangle){0, 0, 16, 16}, (Rectangle){0, 0, 16, 16}};
const Rectangle idle_down[] = {(Rectangle){0, 16, 16, 16}, (Rectangle){0, 16, 16, 16}, (Rectangle){0, 16, 16, 16}, (Rectangle){0, 16, 16, 16}};

Rectangle current_animation;
Rectangle attack_hitbox;

int current_frame = 0;
int frames_counter = 0;
int frame_speed = 6;

float attack_time = 0;
int timer = 0;

bool attacking;

DIRECTION direction;

void player_init(State *g_state)
{
    direction = DOWN;
    current_animation = idle_down[current_frame];
    attacking = false;
    attack_hitbox = (Rectangle){g_state->Player.position.x, g_state->Player.position.y + 16, 16, 16};
    g_state->Player.active = true;
}

void animation_handler()
{
    frames_counter++;

    if (frames_counter >= (60 / frame_speed))
    {
        frames_counter = 0;
        current_frame += 1;

        if (current_frame > 3)
        {
            current_frame = 0;
        }
    }
}

void attack(State *g_state)
{
    attacking = true;
    if (CheckCollisionRecs(attack_hitbox, g_state->Ball.hitbox))
    {
        if (g_state->Player.position.x < g_state->Ball.position.x)
        {
            g_state->Ball.velocity.x += Clamp(fabs(10 / (1 + fabsf((g_state->Ball.position.y + 8) - (g_state->Player.position.y + 8)))), 0, 40);
        }
        else
        {
            g_state->Ball.velocity.x -= Clamp(fabs(10 / (1 + fabsf((g_state->Ball.position.y + 8) - (g_state->Player.position.y + 8)))), 0, 40);
        }

        if (g_state->Player.position.y < g_state->Ball.position.y)
        {
            g_state->Ball.velocity.y += Clamp(fabs(10 / (1 + fabsf((g_state->Ball.position.x + 8) - (g_state->Player.position.x + 8)))), 0, 40);
        }
        else
        {
            g_state->Ball.velocity.y -= Clamp(fabs(10 / (1 + fabsf((g_state->Ball.position.x + 8) - (g_state->Player.position.x + 8)))), 0, 40);
        }
    }
}

void player_update(State *g_state)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        velocity.x += 10;
        direction = RIGHT;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        velocity.x -= 10;
        direction = LEFT;
    }
    else
    {
        velocity.x = 0;
    }

    if (IsKeyDown(KEY_UP))
    {
        velocity.y -= 10;
        direction = UP;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        velocity.y += 10;
        direction = DOWN;
    }
    else
    {
        velocity.y = 0;
    }

    velocity.x *= .87f;
    velocity.y *= .87f;

    if (velocity.x > 0)
    {
        current_animation = walk_right[current_frame];
    }
    else if (velocity.x < 0)
    {
        current_animation = walk_left[current_frame];
    }
    else if (velocity.y > 0)
    {
        current_animation = walk_down[current_frame];
    }
    else if (velocity.y < 0)
    {
        current_animation = walk_up[current_frame];
    }
    else
    {
        switch (direction)
        {
        case UP:
            current_animation = idle_up[current_frame];
            break;
        case DOWN:
            current_animation = idle_down[current_frame];
            break;
        case LEFT:
            current_animation = idle_left[current_frame];
            break;
        case RIGHT:
            current_animation = idle_right[current_frame];
            break;
        }
    }

    if (IsKeyPressed(KEY_X))
    {
        attack(g_state);
    }

    if (attacking)
    {
        attack_time += GetFrameTime();
        if (attack_time > .15)
        {
            attacking = false;
            attack_time = 0;
        }
    }

    switch (direction)
    {
    case UP:
        attack_hitbox = (Rectangle){g_state->Player.position.x, g_state->Player.position.y - 8, 16, 8};
        break;
    case DOWN:
        attack_hitbox = (Rectangle){g_state->Player.position.x, g_state->Player.position.y + 16, 16, 8};
        break;
    case LEFT:
        attack_hitbox = (Rectangle){g_state->Player.position.x - 6, g_state->Player.position.y, 8, 16};
        break;
    case RIGHT:
        attack_hitbox = (Rectangle){g_state->Player.position.x + 14, g_state->Player.position.y, 8, 16};
        break;
    }

    g_state->Player.position.x += (velocity.x * GetFrameTime());
    g_state->Player.position.y += velocity.y * GetFrameTime();

    g_state->Player.hitbox = (Rectangle){g_state->Player.position.x, g_state->Player.position.y, 16, 16};

    animation_handler();
}

void player_draw(State *g_state)
{
    if (attacking)
    {
        // DrawRectangleRec(attack_hitbox, RED);

        switch (direction)
        {
        case UP:
            DrawTextureRec(g_state->spritesheet, (Rectangle){48, 64, 16, 16}, (Vector2){attack_hitbox.x, attack_hitbox.y - 4}, WHITE);
            break;
        case DOWN:
            DrawTextureRec(g_state->spritesheet, (Rectangle){32, 64, 16, 16}, (Vector2){attack_hitbox.x, attack_hitbox.y - 4}, WHITE);
            break;
        case LEFT:
            DrawTextureRec(g_state->spritesheet, (Rectangle){16, 64, 16, 16}, (Vector2){attack_hitbox.x - 4, attack_hitbox.y}, WHITE);
            break;
        case RIGHT:
            DrawTextureRec(g_state->spritesheet, (Rectangle){0, 64, 16, 16}, (Vector2){attack_hitbox.x - 4, attack_hitbox.y}, WHITE);
            break;
        }
    }

    // DrawText(TextFormat("%f", velocity.x), 100, 100, 10, RED);
    // DrawText(TextFormat("%f", velocity.y), 100, 120, 10, RED);
    // DrawRectangleRec(g_state->Player.hitbox, RED);

    DrawTextureRec(g_state->spritesheet, current_animation, g_state->Player.position, (WHITE));
}