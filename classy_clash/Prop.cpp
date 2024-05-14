#include "raylib.h"
#include "raymath.h"
#include "Prop.h"

Prop::Prop()
{
}

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos), texture(tex)
{
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = {Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, scale, 0.0f, WHITE);
}
