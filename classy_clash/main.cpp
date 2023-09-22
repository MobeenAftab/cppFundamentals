#include "raylib.h"
#include "raymath.h"

int main(void)
{
    const int screenWidth = 384;
    const int screenHeight = 384;

    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = {0.0, 0.0};

    const float speed = 4.0;

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

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();

    return 0;
}