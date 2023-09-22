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
        }

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        DrawTexturePro(knight, knightRec, knightDest, Vector2{}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight);
    CloseWindow();

    return 0;
}