#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main(void)
{
    const int screenWidth = 384;
    const int screenHeight = 384;

    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = {0.0, 0.0};
    const float mapScale = {4.0f};

    Character knight{screenWidth, screenHeight};
    Prop rock{Vector2{0.0f, 0.0f}, LoadTexture("nature_tileset/Rock.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());

        rock.Render(knight.getWorldPos());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + screenWidth > map.width * mapScale ||
            knight.getWorldPos().y + screenHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();

    return 0;
}