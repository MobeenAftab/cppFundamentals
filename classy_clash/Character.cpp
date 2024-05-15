#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Character::Character(int winWidth, int winHeight) : winWidth(winWidth), winHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return {static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
            static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;

    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;

    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;

    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.0f : 0.0f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.0f : 0.0f;
    }

    // draw weapon
    Rectangle source{0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y,
                   weapon.width * scale, weapon.height * scale};

    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRec.x,
        weaponCollisionRec.y,
        weaponCollisionRec.width,
        weaponCollisionRec.height,
        RED);
}

void Character::takeDamage(float damage)
{
    health -= damage;

    if (health <= 0.f)
    {
        setAlive(false);
    }
}
