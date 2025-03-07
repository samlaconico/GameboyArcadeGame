#include "raylib.h"
#include "state.h"
#include "cursor.h"
#include "player.h"
#include "ball.h"
#include "enemy.h"
#include "defs.h"

typedef enum SCREEN
{
    TITLE,
    GAME
} SCREEN;

SCREEN screen;

int level[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
               6, 7, 7, 7, 7, 7, 7, 7, 7, 8};

void game_init(State *g_state)
{
    screen = GAME;

    g_state->score = 0;
    g_state->spritesheet = LoadTexture("sprites.png");
    g_state->Ball.position = (Vector2){50, 50};

    for (int i = 0; i < 10; i++)
    {
        g_state->enemy_list[i].position = (Vector2){GetRandomValue(3, 140), GetRandomValue(3, 126)};
        enemy_init(g_state, &g_state->enemy_list[i]);
    }

    player_init(g_state);
}

void game_update(State *g_state)
{
    switch (screen)
    {
    case GAME:
        if (g_state->Player.active)
            player_update(g_state);
        ball_update(g_state);

        for (int i = 0; i < 10; i++)
        {
            if (g_state->enemy_list[i].active)
                enemy_update(g_state, &g_state->enemy_list[i]);
        }
        break;
    case TITLE:
        break;
    }
}

void level_draw(State *g_state)
{
    for (int i = 0; i < 10; i++)
    {
        for (int k = 0; k < 9; k++)
        {
            int pos = (k * 10) + i;
            DrawTextureRec(g_state->spritesheet, (Rectangle){level[pos] * 16, 80, 16, 16}, (Vector2){i * 16, k * 16}, WHITE);
        }
    }
}

void game_draw(State *g_state)
{
    switch (screen)
    {
    case GAME:
        ClearBackground((Color){155, 188, 15, 255});

        level_draw(g_state);

        DrawText(TextFormat("SCORE: %d", g_state->score), (GAME_WIDTH / 2) - ((MeasureText(TextFormat("SCORE: %d", g_state->score), 1) / 2)), 20, 1, (Color){15, 56, 15, 255});
        DrawText(TextFormat("SCORE: %d", g_state->score), (GAME_WIDTH / 2) - ((MeasureText(TextFormat("SCORE: %d", g_state->score), 1) / 2)) - 1, 19, 1, (Color){155, 188, 15, 255});

        if (g_state->Player.position.y < g_state->Ball.position.y)
        {
            if (g_state->Player.active)
                player_draw(g_state);

            ball_draw(g_state);
        }
        else
        {
            ball_draw(g_state);

            if (g_state->Player.active)
                player_draw(g_state);
        }

        for (int i = 0; i < 10; i++)
        {
            if (g_state->enemy_list[i].active)
                enemy_draw(g_state, &g_state->enemy_list[i]);
        }
        break;

    case TITLE:
        break;
    }
}
