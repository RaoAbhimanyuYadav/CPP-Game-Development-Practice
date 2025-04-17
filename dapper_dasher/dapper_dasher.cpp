#include "raylib.h"

#define WINDOW_X 600
#define WINDOW_Y 400
#define WINDOW_TITLE "DAPPER DASHER"
#define FPS 60
#define BACKGROUND_COL WHITE

#define JUMP_VELOCITY -500

#define FRAME_UPDATE_TIME 1.0 / 12.0 // 12 frames in 1 sec

#define ENEMY_CNT 10

struct AnimeConfig
{
    Rectangle rec;
    Vector2 pos;
    int frame;
};

void drawBackgound(float &posX, const Texture2D &texture, const int vel, const float zoom, const float deltaTime)
{

    posX += vel * deltaTime;
    if (posX <= texture.width * -zoom)
        posX = 0;

    Vector2 bg1Pos{posX, 0};
    DrawTextureEx(texture, bg1Pos, 0, zoom, WHITE);

    Vector2 bg2Pos{posX + texture.width * zoom, 0};
    DrawTextureEx(texture, bg2Pos, 0, zoom, WHITE);
}

bool detectCollision(AnimeConfig &item1, AnimeConfig &item2)
{
    const int pad = 20;
    Rectangle rec1{
        .x = item1.pos.x + pad,
        .y = item1.pos.y + pad,
        .width = item1.rec.width - 2 * pad,
        .height = item1.rec.height - 2 * pad};
    Rectangle rec2{
        .x = item2.pos.x + pad,
        .y = item2.pos.y + pad,
        .width = item2.rec.width - 2 * pad,
        .height = item2.rec.height - 2 * pad};

    return CheckCollisionRecs(rec1, rec2);
}

int main()
{
    InitWindow(WINDOW_X, WINDOW_Y, WINDOW_TITLE);
    SetTargetFPS(FPS);

    // pixel/frame without delta time, for pixel/sec multiple with delta time
    int jumpVelocity{0};
    const int acceleration{1'000};
    bool isInAir{};

    // charcter frame running duration
    float frameRunningTime{};

    // enemy character
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimeConfig nebulaConfVec[ENEMY_CNT];
    for (int idx = 0; idx < ENEMY_CNT; idx++)
    {
        nebulaConfVec[idx].rec = {0, 0, nebula.width / 8, nebula.height / 8};
        nebulaConfVec[idx].pos = {static_cast<float>(WINDOW_X + 500 * idx), 1.0f * WINDOW_Y - nebula.height / 8};
        nebulaConfVec[idx].frame = 0;
    }
    const int nebulaVel = -300;

    // main character
    Texture2D scarfy = LoadTexture("./textures/scarfy.png");
    AnimeConfig scarfyConf{
        {0, 0, scarfy.width / 6, scarfy.height},
        {0, WINDOW_Y - scarfy.height},
        0};

    // background
    Texture2D background = LoadTexture("./textures/far-buildings.png");
    float backgroundX{};
    const int backgroundVel{-50};

    // mid ground
    Texture2D midGround = LoadTexture("./textures/back-buildings.png");
    float midGroundX{};
    const int midGroundVel{-100};

    // foreground
    Texture2D foreGround = LoadTexture("./textures/foreground.png");
    float foreGroundX{};
    const int foreGroundVel{-150};

    // finish line
    float finishX{nebulaConfVec[ENEMY_CNT - 1].pos.x + nebula.width / 8};
    bool collided{};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND_COL);

        // delta time
        float dt{GetFrameTime()};

        drawBackgound(backgroundX, background, backgroundVel, 2.4, dt);
        drawBackgound(midGroundX, midGround, midGroundVel, 2.4, dt);
        drawBackgound(foreGroundX, foreGround, foreGroundVel, 2.4, dt);

        if (!collided)
        {
            // Jump Button pressed
            if (IsKeyPressed(KEY_SPACE) && !isInAir && finishX >= 0)
                jumpVelocity += JUMP_VELOCITY;

            // enemy position calculation
            for (int idx = 0; idx < ENEMY_CNT; idx++)
                nebulaConfVec[idx].pos.x += nebulaVel * dt;

            finishX += nebulaVel * dt;
            if (finishX <= 0)
            {
                DrawText("GAME COMPLETED", WINDOW_X / 10, WINDOW_Y / 2, 50, RED);
            }

            // main character position in air
            scarfyConf.pos.y += jumpVelocity * dt;

            // frame
            frameRunningTime += dt;
            if (frameRunningTime >= FRAME_UPDATE_TIME)
            {
                frameRunningTime = 0;

                for (int idx = 0; idx < ENEMY_CNT; idx++)
                {
                    if (++nebulaConfVec[idx].frame >= 8)
                        nebulaConfVec[idx].frame = 0;
                    nebulaConfVec[idx].rec.x = nebulaConfVec[idx].frame * nebulaConfVec[idx].rec.width;
                }

                if (!isInAir)
                {
                    if (++scarfyConf.frame >= 5)
                        scarfyConf.frame = 0;
                    scarfyConf.rec.x = scarfyConf.frame * scarfyConf.rec.width;
                }
            }

            // main character in the air
            if (scarfyConf.pos.y < WINDOW_Y - scarfy.height)
            {
                jumpVelocity += acceleration * dt;
                isInAir = true;
            }
            else
            { // main character present on ground
                jumpVelocity = 0;
                isInAir = false;
            }
        }

        for (int idx = 0; idx < ENEMY_CNT; idx++)
        {
            collided |= detectCollision(nebulaConfVec[idx], scarfyConf);
        }

        if (collided)
        {
            DrawText("GAME OVER", WINDOW_X / 4, WINDOW_Y / 2, 50, RED);
        }
        else
        {
        }

        // draw enemy character
        for (int idx = 0; idx < ENEMY_CNT; idx++)
            DrawTextureRec(nebula, nebulaConfVec[idx].rec, nebulaConfVec[idx].pos, RED);

        // draw main character
        DrawTextureRec(scarfy, scarfyConf.rec, scarfyConf.pos, WHITE);
        EndDrawing();
    }

    // free memory
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    UnloadTexture(background);
    UnloadTexture(midGround);
    UnloadTexture(foreGround);

    // auto closure
    CloseWindow();
}