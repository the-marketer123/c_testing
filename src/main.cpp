#include <raylib.h>
#include "ball.h"

int main() 
{
    const Color backcolor = {170, 170, 255, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    Ball ball;
    
    InitWindow(screenWidth, screenHeight, "ball");
    SetTargetFPS(144);
    
    while (!WindowShouldClose())
    {
        ball.Update();
        
        BeginDrawing();
            ClearBackground(backcolor);
            ball.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}