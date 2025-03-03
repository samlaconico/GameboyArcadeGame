#pragma once
#include "raylib.h"
#define MAX_UNITS 100

struct Player
{
    bool active;
    Vector2 position;
    Rectangle hitbox;
    int health;
} Player;

typedef struct Enemy
{
    bool active;
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
    float attack_timer;
    int health;
} Enemy;

struct Ball
{
    bool active;
    bool moving;
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
} Ball;

typedef struct State
{
    RenderTexture2D render_texture;
    Texture2D spritesheet;
    struct Cursor
    {
        Vector2 position;
        Rectangle hitbox;
    } Cursor;

    struct Player Player;
    struct Ball Ball;
    int score;
    struct Enemy enemy_list[10];
} State;
