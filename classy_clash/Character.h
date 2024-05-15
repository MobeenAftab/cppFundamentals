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
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;

private:
    int winWidth{};
    int winHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
};

#endif
