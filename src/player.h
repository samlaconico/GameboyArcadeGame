#include "state.h"

typedef enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} DIRECTION;

Vector2 velocity;

void player_init(State *g_state);
void player_update(State *g_state);
void player_draw(State *g_state);
void animation_handler();
void attack();