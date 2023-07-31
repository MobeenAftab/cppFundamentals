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

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // body of texture, calculate the size of each image in sprite sheet using local coordinates
    Rectangle nebulaRec{0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f};

    // where to place texture in game window
    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // animimation frame (image from sprite sheet to be used)
    int frame{};
    int nebulaFrame{};

    int velocity{0};
    // (pixel/second)
    int jumpValue{-600};
    bool isInAir{};

    // how much time should pass between animation frames
    // update animation 12 times per second
    const float updateTime{1.0 / 12.0};
    float runnningTime{};

    const float nebulaUpdateTime{1.0 / 12.0};
    float nebulaRunnningTime{};

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

        // update nebula position
        nebulaPos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        // update running time
        runnningTime += dT;

        if (!isInAir)
        {

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
        }

        if (nebulaRunnningTime >= nebulaUpdateTime)
        {
            nebulaRunnningTime = 0;

            // update animation frame
            nebulaRec.x = nebulaFrame * nebulaRec.width;
            nebulaFrame++;
            if (nebulaFrame > 7)
            {
                nebulaFrame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    return 0;
}