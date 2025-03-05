#pragma once
#include "raylib.h"
#define MAX_UNITS 100

struct Player
{
    bool active;
    Vector2 position;
    Rectangle hitbox;
    Texture2D hurt_texture;
    int health;
} Player;

typedef struct Enemy
{
    bool active, hurt;
    Vector2 position, velocity;
    Rectangle hitbox;
    Texture2D hurt_texture;
    float attack_timer, hurt_timer;
    int health;
} Enemy;

struct Ball
{
    bool active, moving;
    Vector2 position, velocity;
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
    struct Enemy enemy_list[10];

    int score;
    bool exit;
} State;
