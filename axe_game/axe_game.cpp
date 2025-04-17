#include <iostream>
#include <raylib.h>

using namespace std;

#define CIRCLE_COL BLUE
#define CIRCLE_RAD 100
#define BACKGROUND_COL RED
#define WINDOW_X 500
#define WINDOW_Y 400
#define WINDOW_NAME "ABHI"
#define REC_COL BLACK
#define REC_X 100
#define REC_Y 50

bool collision_dectector(int circle_x, int circle_y, int rec_x, int rec_y)
{
    int l_circle_x{circle_x - CIRCLE_RAD}, r_circle_x{circle_x + CIRCLE_RAD};
    int t_circle_y{circle_y - CIRCLE_RAD}, b_circle_y{circle_y + CIRCLE_RAD};

    int l_axe_x{rec_x}, r_axe_x{rec_x + REC_X};
    int t_axe_y{rec_y}, b_axe_y{rec_y + REC_Y};

    if (b_axe_y >= t_circle_y && t_axe_y <= b_circle_y && l_axe_x <= r_circle_x && r_axe_x >= l_circle_x)
        return true;
    return false;
}

int main()
{
    InitWindow(WINDOW_X, WINDOW_Y, WINDOW_NAME);
    SetTargetFPS(10);

    int circle_x{25}, circle_y{200};

    int rec_x{200}, rec_y{0}, rec_dir{1};

    bool collision{};

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BACKGROUND_COL);

        if (collision)
        {
            DrawText("GAME OVER", WINDOW_X / 2 - 100, WINDOW_Y / 2 - 5, 20, WHITE);
        }
        else
        {

            DrawRectangle(rec_x, rec_y, REC_X, REC_Y, REC_COL);
            DrawCircle(circle_x, circle_y, CIRCLE_RAD, CIRCLE_COL);

            if (IsKeyDown(KEY_RIGHT))
                circle_x += 10;
            if (IsKeyDown(KEY_LEFT))
                circle_x -= 10;

            rec_y += 10 * rec_dir;
            if (rec_y >= WINDOW_Y - REC_Y || rec_y <= 0)
                rec_dir = -rec_dir;

            collision = collision_dectector(circle_x, circle_y, rec_x, rec_y);
        }

        EndDrawing();
    }
    return 0;
}