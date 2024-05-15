#include "raylib.h"

class Enemy
{
public:
    Enemy();
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    Vector2 getWorldPos() { return worldPos; }
    Rectangle getCollisionRec();
    void undoMovement();
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
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
};
