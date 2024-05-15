#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle enemyRec{
        frame * width,
        0.0f,
        rightLeft * width,
        height};
    Rectangle enemyDest{
        screenPos.x, screenPos.y, scale * width, scale * height};

    DrawTexturePro(texture, enemyRec, enemyDest, Vector2{}, 0.0f, WHITE);
}
