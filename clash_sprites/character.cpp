#include "character.hpp"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : winWidth(winWidth), winHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1;
    if (IsKeyDown(KEY_D))
        velocity.x += 1;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1;
    if (IsKeyDown(KEY_S))
        velocity.y += 1;

    BaseCharacter::tick(deltaTime);
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (leftright > 0.f)
    {
        origin = {0, weapon.height * scale};
        offset = {35.f, 55.f};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * leftright, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, static_cast<float>(weapon.width) * scale, static_cast<float>(weapon.height) * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    weaponCollisionRec.x = dest.x - origin.x;
    weaponCollisionRec.y = dest.y - origin.y;
    weaponCollisionRec.width = dest.width;
    weaponCollisionRec.height = dest.height;

    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * 0.5f * height,
    };
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}