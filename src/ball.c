#include "ball.h"
#include "raymath.h"

void ball_init(State *g_state)
{
    g_state->Ball.active = true;
}

void ball_update(State *g_state)
{
    g_state->Ball.hitbox = (Rectangle){g_state->Ball.position.x + 2, g_state->Ball.position.y + 2, 12, 12};

    if (!CheckCollisionRecs(g_state->Ball.hitbox, g_state->Player.hitbox))
        g_state->Ball.velocity = Vector2Scale(g_state->Ball.velocity, .89);
    g_state->Ball.position.x += g_state->Ball.velocity.x;
    g_state->Ball.position.y += g_state->Ball.velocity.y;

    if (!Vector2Equals(g_state->Ball.velocity, (Vector2){0, 0}))
        g_state->Ball.moving = true;
    else
        g_state->Ball.moving = false;

    if ((g_state->Ball.position.x + g_state->Ball.hitbox.width) + g_state->Ball.velocity.x >= 157 ||
        (g_state->Ball.position.x) + g_state->Ball.velocity.x <= 3 || CheckCollisionRecs((Rectangle){g_state->Ball.hitbox.x + g_state->Ball.velocity.x, g_state->Ball.hitbox.y}, g_state->Player.hitbox))
    {
        g_state->Ball.velocity.x *= -1;
    }

    if ((g_state->Ball.position.y + g_state->Ball.hitbox.height) + g_state->Ball.velocity.y >= 141 ||
        (g_state->Ball.position.y) + g_state->Ball.velocity.y <= 3 || CheckCollisionRecs((Rectangle){g_state->Ball.hitbox.x, g_state->Ball.hitbox.y + g_state->Ball.velocity.y}, g_state->Player.hitbox))
    {
        g_state->Ball.velocity.y *= -1;
    }
}

void ball_draw(State *g_state)
{
    // DrawRectangleRec(g_state->Ball.hitbox, RED);

    DrawTextureRec(g_state->spritesheet, (Rectangle){32, 32, 16, 16}, g_state->Ball.position, WHITE);
}