#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy();
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    virtual void tick(float deltaTime) override;

private:
};
