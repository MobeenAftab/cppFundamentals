#include "raylib.h"
#include "raymath.h"
#include "Prop.h"

Prop::Prop()
{
}

Prop::Prop(Texture2D tex, Vector2 pos) : texture(tex), worldPos(pos)
{
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = {Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos = {Vector2Subtract(worldPos, knightPos)};

    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale};
}
