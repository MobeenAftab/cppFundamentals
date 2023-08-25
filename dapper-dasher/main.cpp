#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{

    int windowsDimensiosn[2];
    windowsDimensiosn[0] = 512; // Width
    windowsDimensiosn[1] = 380; // Height

    InitWindow(windowsDimensiosn[0], windowsDimensiosn[1], "Dapper Dasher");

    // acceleration due to gravity (pixel/second)/second
    const int gravity{1'000};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

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

    const int sizeOfNebulae = 10;
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8.0;
        nebulae[i].rec.height = nebula.height / 8.0;
        nebulae[i].pos.y = windowsDimensiosn[1] - nebula.height / 8;
        nebulae[i].pos.x = windowsDimensiosn[0] + i * 300;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
    }

    float finishLine{nebulae[sizeOfNebulae - 1].pos.x};

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

        // Scroll background
        bgX -= 20 * dT; // Move left 20 pixels per second
        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }

        // Scroll the midground
        mgX -= 40 * dT;
        if (mgX <= -midground.width * 2)
        {
            mgX = 0.0;
        }
        // Scroll the foreground
        fgX -= 80 * dT;
        if (fgX <= -foreground.width * 2)
        {
            fgX = 0.0;
        }

        // draw the background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // draw the midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // draw the foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        // ground check
        if (isOnGround(scarfydata, windowsDimensiosn[1]))
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
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        // update finishLine
        finishLine += nebVel * dT;

        // update scarfy position
        scarfydata.pos.y += velocity * dT;

        // update running time
        scarfydata.runningTime += dT;

        if (!isInAir)
        {
            scarfydata = updateAnimData(scarfydata, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        DrawTextureRec(scarfy, scarfydata.rec, scarfydata.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    return 0;
}