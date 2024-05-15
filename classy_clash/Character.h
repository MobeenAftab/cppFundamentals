#ifndef CHARCTER_H
#define CHARCTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character();
    Character(int winWidth, int winHeight);
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;

private:
    int winWidth{};
    int winHeight{};
    float health{100.0f};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    void drawCollisionRectangleLines(Rectangle rec);
};

#endif
