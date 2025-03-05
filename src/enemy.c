#include "enemy.h"
#include "raymath.h"

Image hurt_image;

void enemy_init(State *g_state, Enemy *e)
{
    e->attack_timer = 0;
    e->active = true;
    e->health = 3;
    e->hurt = false;

    hurt_image = LoadImageFromTexture(g_state->spritesheet);
    ImageColorReplace(&hurt_image, (Color){15, 56, 15, 255}, WHITE);
    ImageColorReplace(&hurt_image, (Color){139, 172, 15, 255}, WHITE);
    ImageColorReplace(&hurt_image, (Color){48, 98, 48, 255}, WHITE);
    ImageColorReplace(&hurt_image, (Color){155, 188, 15, 255}, WHITE);

    e->hurt_texture = LoadTextureFromImage(hurt_image);
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

    if ((e->hitbox.x + e->hitbox.width) + e->velocity.x > 157 || e->hitbox.x < 3)
    {
        e->velocity.x *= -1;
    }

    if ((e->hitbox.y + e->hitbox.height) + e->velocity.y > 141 || e->hitbox.y < 3)
    {
        e->velocity.y *= -1;
    }

    if (CheckCollisionRecs(e->hitbox, g_state->Ball.hitbox) && (g_state->Ball.velocity.x > 1 || g_state->Ball.velocity.x < -1 || g_state->Ball.velocity.y > 1 || g_state->Ball.velocity.y < -1) && e->hurt == false)
    {
        g_state->Ball.velocity.x *= -1;
        g_state->Ball.velocity.y *= -1;

        hurt_self(e);
    }

    if (e->hurt)
    {
        e->hurt_timer += GetFrameTime();
    }

    if (e->hurt_timer > .2f)
    {
        e->hurt = false;
        e->hurt_timer = 0;
    }

    if (e->health == 0)
    {
        e->active = false;
        g_state->score += 100;
    }

    e->velocity.x *= .94f;
    e->velocity.y *= .94f;

    e->position.x += e->velocity.x * GetFrameTime();
    e->position.y += e->velocity.y * GetFrameTime();
}

void hurt_self(Enemy *e)
{
    e->health -= 1;
    e->hurt = true;
}

void enemy_draw(State *g_state, Enemy *e)
{
    // DrawRectangleRec(e->hitbox, RED);
    DrawTextureRec(e->hurt ? e->hurt_texture : g_state->spritesheet, (Rectangle){64, 16, 16, 16}, e->position, WHITE);
}