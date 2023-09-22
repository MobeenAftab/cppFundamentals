#include "raylib.h"
#include "raymath.h"

int main(void)
{
    const int screenWidth = 384;
    const int screenHeight = 384;
    const float speed = 4.0f;

    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = {0.0, 0.0};

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)screenWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)screenHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};
    Rectangle knightRec{
        0.0f,
        0.0f,
        (float)knight.width / 6.0f,
        (float)knight.height};
    Rectangle knightDest{
        knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};

    // 1: facing right, -1 : facing left
    float rightLeft{1.f};

    // Animation variables
    float runningTime{};
    // frame is refering to what frame in sprite sheet
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / 12.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;

        if (IsKeyDown(KEY_D))
            direction.x += 1.0;

        if (IsKeyDown(KEY_W))
            direction.y -= 1.0;

        if (IsKeyDown(KEY_S))
            direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knightRun;
        }
        else
        {
            knight = knightIdle;
        }

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrame)
                frame = 0;
        }

        // Flip sprite x direction depending on key down direction
        knightRec.x = frame * (float)knight.width / 6.0f;
        knightRec.width = rightLeft * (float)knight.width / 6.0f;
        DrawTexturePro(knight, knightRec, knightDest, Vector2{}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight);
    UnloadTexture(knightRun);
    UnloadTexture(knightIdle);

    CloseWindow();

    return 0;
}