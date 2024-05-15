#ifndef CHARCTER_H
#define CHARCTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character();
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;

private:
    int winWidth{};
    int winHeight{};
};

#endif
