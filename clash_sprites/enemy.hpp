#include "baseCharacter.hpp"
#include "character.hpp"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle, Texture2D run);
    virtual void tick(float deltaTime) override;
    void setTarget(Character *character) { target = character; }
    virtual Vector2 getScreenPos() override;

private:
    Character *target;
};