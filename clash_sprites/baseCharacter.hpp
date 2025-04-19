
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() const { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    // character texture
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 worldPos{};
    // character face direction -1:left facing, 1:right facing
    float leftright{1};
    // frame updation
    float runningTime{};
    const float updateTime{1.0f / 12.0f};
    // current frame
    int frame{};
    int maxFrames{6};
    // speed of movement
    float speed{4.0f};
    // character width
    float width{};
    float height{};
    float scale{4.0f};
    // last position
    Vector2 lastFrameWorldPos{};
    Vector2 velocity{};

private:
    bool alive{1};
};

#endif