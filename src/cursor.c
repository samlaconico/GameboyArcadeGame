#include "cursor.h"

void cursor_init(State *g_state)
{
    g_state->Cursor.position = (Vector2){128, 128};
}

void cursor_update(State *g_state)
{
    g_state->Cursor.hitbox = (Rectangle){g_state->Cursor.position.x, g_state->Cursor.position.y, 8, 8};

    if (IsKeyPressed(KEY_RIGHT))
    {
        g_state->Cursor.position.x += 8;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        g_state->Cursor.position.x -= 8;
    }

    if (IsKeyPressed(KEY_UP))
    {
        g_state->Cursor.position.y -= 8;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        g_state->Cursor.position.y += 8;
    }
}

void cursor_draw(State *g_state)
{
    DrawTextureRec(g_state->spritesheet, (Rectangle){0, 0, 16, 16}, g_state->Cursor.position, WHITE);
}
