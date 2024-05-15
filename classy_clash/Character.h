#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character();
    Character(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
};