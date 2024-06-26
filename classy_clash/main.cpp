#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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

    Enemy goblin(Vector2{200.0f, 200.0f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png"));

    Enemy slime(Vector2{250.0f, 250.0f},
                LoadTexture("characters/slime_idle_spritesheet.png"),
                LoadTexture("characters/slime_run_spritesheet.png"));

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

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

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
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

        goblin.setTarget(&knight);

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs((knight.getWeaponCollisionRec()), goblin.getCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);

    CloseWindow();

    return 0;
}