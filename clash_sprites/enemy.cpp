#include "enemy.hpp"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle, Texture2D run)
{
    worldPos = pos;
    texture = idle;
    BaseCharacter::run = run;
    BaseCharacter::idle = idle;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    // BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
