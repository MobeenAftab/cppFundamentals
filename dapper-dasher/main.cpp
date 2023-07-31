#include "raylib.h"

int main()
{
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // acceleration due to gravity (pixel/second)/second
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfy.height;

    // animimation frame
    int frame{};

    int velocity{0};
    // (pixel/second)
    int jumpValue{-600};
    bool isInAir{};

    // amount of time before we update the animation time
    // cycle through sprite sheet once every 12th of a second
    const float updateTime{1.0 / 12.0};
    float runnningTime{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // delta time (time since last frame)
        const float dT = GetFrameTime();

        // ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpValue;
        }

        // update the position
        scarfyPos.y += velocity * dT;

        // update running time
        runnningTime += dT;

        if (runnningTime >= updateTime)
        {
            runnningTime = 0;
            // update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
    return 0;
}