
#include "raylib.h"
#include "state.h"
#include "defs.h"
#include "game.h"
#include "stdlib.h"
#include "resource_dir.h"

int loop(State *g_state)
{
	// update
	game_update(g_state);

	// draw to render texture
	BeginTextureMode(g_state->render_texture);
	ClearBackground(BLACK);
	game_draw(g_state);
	EndTextureMode();

	// draw render texture to screen size
	BeginDrawing();
	DrawTexturePro(g_state->render_texture.texture, (Rectangle){0.0f, 0.0f, g_state->render_texture.texture.width, -g_state->render_texture.texture.height},
				   (Rectangle){(GetScreenWidth() - (GAME_WIDTH * SCREEN_SCALE)) * 0.5f, (GetScreenHeight() - (GAME_HEIGHT * SCREEN_SCALE)) * 0.5f,
							   GAME_WIDTH * SCREEN_SCALE, GAME_HEIGHT * SCREEN_SCALE},
				   (Vector2){0, 0}, 0.0f, WHITE);
	EndDrawing();
}

int main()
{
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GBC TD");
	SearchAndSetResourceDir("resources");

	State *g_state = malloc(sizeof(State));
	g_state->render_texture = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	game_init(g_state);

	while (!WindowShouldClose())
	{
		loop(g_state);
	}

	CloseWindow();
	return 0;
}
