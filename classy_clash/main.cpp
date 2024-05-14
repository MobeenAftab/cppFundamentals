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
    Prop rock{LoadTexture("nature_tileset/Rock.png"), Vector2{0.f, 0.f}};

    Prop props[2]{
        Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{300.f, 600.f}},
        Prop{LoadTexture("nature_tileset/Log.png"), Vector2{200.f, 400.f}}};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + screenWidth > map.width * mapScale ||
            knight.getWorldPos().y + screenHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        };

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();

    return 0;
}