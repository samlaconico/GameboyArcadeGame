#include "enemy.h"
#include "raymath.h"

void enemy_init(State *g_state, Enemy *e)
{
    e->attack_timer = 0;
    e->active = true;
}
void enemy_update(State *g_state, Enemy *e)
{
    e->hitbox = (Rectangle){e->position.x, e->position.y, 16, 16};
    e->attack_timer += GetFrameTime();

    if (e->attack_timer > GetRandomValue(3, 20))
    {
        e->velocity.x = (GetRandomValue(-100, 100));
        e->velocity.y = (GetRandomValue(-100, 100));
        e->attack_timer = 0;
    }

    if ((e->hitbox.x + e->hitbox.width) + e->velocity.x > 160 || e->hitbox.x < 0)
    {
        e->velocity.x *= -1;
    }

    if ((e->hitbox.y + e->hitbox.height) + e->velocity.y > 144 || e->hitbox.y < 0)
    {
        e->velocity.y *= -1;
    }

    if (CheckCollisionRecs(e->hitbox, g_state->Ball.hitbox) && (g_state->Ball.velocity.x > 1 || g_state->Ball.velocity.x < -1 || g_state->Ball.velocity.y > 1 || g_state->Ball.velocity.y < -1))
    {
        g_state->Ball.velocity.x *= -1;
        g_state->Ball.velocity.y *= -1;

        e->active = false;

        g_state->score += 100;
    }

    e->velocity.x *= .94f;
    e->velocity.y *= .94f;

    e->position.x += e->velocity.x * GetFrameTime();
    e->position.y += e->velocity.y * GetFrameTime();
}
void enemy_draw(State *g_state, Enemy *e)
{
    // DrawRectangleRec(e->hitbox, RED);
    DrawTextureRec(g_state->spritesheet, (Rectangle){64, 16, 16, 16}, e->position, WHITE);
}