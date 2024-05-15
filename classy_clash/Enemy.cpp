#include "Enemy.h"
#include "raymath.h"

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
    speed = 3.5f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive())
        return;

    // get targets current location
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    // stop chasing if target is within radius
    if (Vector2Length(velocity) < radius)
    {
        velocity = {};
    }

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
    {
        target->takeDamage(damagePerSecond * deltaTime);
    }

    BaseCharacter::tick(deltaTime);
}
