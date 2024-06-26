#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy();
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    void setTarget(Character *character) { target = character; }

private:
    Character *target;
    float damagePerSecond{10.f};
    float radius{25.f};
};

#endif