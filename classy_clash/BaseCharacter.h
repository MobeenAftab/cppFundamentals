#ifndef BASE_CHARCTER_H
#define BASE_CHARCTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    BaseCharacter(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    Rectangle getCollisionRec();
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; };
    void undoMovement();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};
    // 1: facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    // frame is refering to what frame in sprite sheet
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};

private:
    bool alive{true};
};

#endif