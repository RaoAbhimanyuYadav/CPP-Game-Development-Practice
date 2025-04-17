#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "baseCharacter.hpp"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;

private:
    int winWidth{};
    int winHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
};

#endif