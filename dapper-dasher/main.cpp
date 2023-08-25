#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{

    int windowsDimensiosn[2];
    windowsDimensiosn[0] = 512; // Width
    windowsDimensiosn[1] = 380; // Height

    InitWindow(windowsDimensiosn[0], windowsDimensiosn[1], "Dapper Dasher");

    // acceleration due to gravity (pixel/second)/second
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfydata;
    scarfydata.rec.width = scarfy.width / 6;
    scarfydata.rec.height = scarfy.height;
    scarfydata.rec.x = 0;
    scarfydata.rec.y = 0;
    scarfydata.pos.x = windowsDimensiosn[0] / 2 - scarfydata.rec.width / 2;
    scarfydata.pos.y = windowsDimensiosn[1] - scarfy.height;
    scarfydata.frame = 0;
    scarfydata.updateTime = 1.0 / 12.0;
    scarfydata.runningTime = 0.0;

    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebData{
        {0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f},                                // body of texture, calculate the size of each image in sprite sheet using local coordinates
        {windowsDimensiosn[0], static_cast<float>(windowsDimensiosn[1] - nebula.height / 8)}, // where to place texture in game window
        0,
        1.0 / 12.0,
        0

    };

    AnimData nebData2{
        {0.0, 0.0, static_cast<float>(nebula.width / 8), static_cast<float>(nebula.height / 8)},
        {windowsDimensiosn[0] + 300, static_cast<float>(windowsDimensiosn[1] - nebula.height / 8)},
        0,
        1.0 / 16.0,
        0.0

    };

    AnimData nebulae[2]{nebData, nebData2};

    // nebula X velocity (pixels/second)
    int nebVel{-200};
    int velocity{0};
    // (pixel/second)
    int jumpValue{-600};
    bool isInAir{};

    // how much time should pass between animation frames
    // update animation 12 times per second

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // delta time (time since last frame)
        const float dT = GetFrameTime();

        // ground check
        if (scarfydata.pos.y >= windowsDimensiosn[1] - scarfydata.rec.height)
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
        nebulae[0].pos.x += nebVel * dT;

        nebulae[1].pos.x += nebVel * dT;

        // update scarfy position
        scarfydata.pos.y += velocity * dT;

        // update running time
        scarfydata.runningTime += dT;

        if (!isInAir)
        {

            if (scarfydata.runningTime >= scarfydata.updateTime)
            {
                scarfydata.runningTime = 0;

                // update animation frame
                scarfydata.rec.x = scarfydata.frame * scarfydata.rec.width;
                scarfydata.frame++;
                if (scarfydata.frame > 5)
                {
                    scarfydata.frame = 0;
                }
            }
        }

        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0;

            // update animation frame
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0;

            // update animation frame
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfydata.rec, scarfydata.pos, WHITE);
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    return 0;
}