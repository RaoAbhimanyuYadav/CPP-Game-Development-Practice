#include "raylib.h"
#include "raymath.h"
#include "character.hpp"
#include "prop.hpp"
#include "enemy.hpp"

int main()
{
    const int WINDOW_X{384}, WINDOW_Y{384};
    InitWindow(WINDOW_X, WINDOW_Y, "CLASSY CLASH");

    SetTargetFPS(60);

    Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0, 0};
    const float mapScale{4.0f};

    Character knight{WINDOW_X, WINDOW_Y};

    Prop props[2]{
        {Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        {Vector2{300.0f, 600.0f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    goblin.setTarget(&knight);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // map
        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);
        DrawTextureEx(mapTexture, mapPos, 0, mapScale, WHITE);

        // props
        for (auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        // knight movement
        knight.tick(GetFrameTime());

        goblin.tick(GetFrameTime());

        // Boundary checks
        if (knight.getWorldPos().x < 0 ||
            knight.getWorldPos().y < 0 ||
            knight.getWorldPos().x + WINDOW_X > mapTexture.width * mapScale ||
            knight.getWorldPos().y + WINDOW_Y > mapTexture.height * mapScale)
        {
            knight.undoMovement();
        }

        // prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }
    UnloadTexture(mapTexture);
    CloseWindow();
}