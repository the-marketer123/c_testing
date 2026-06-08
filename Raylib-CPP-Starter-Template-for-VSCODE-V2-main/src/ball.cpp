#include "ball.h"
#include <raylib.h>
#include <cmath>
#include <print>
#include <iostream>
#include <random>

std::random_device rd; 
std::mt19937 gen(rd()); 
std::uniform_int_distribution<> distr(50, 150);

Ball::Ball() 
    : x(400)
    , y(0)
    ,speedX(distr(gen))
    , radius(15) 
{
}

static float bounce = 0;
static float range = 200;

void Ball::Update() 
{
    const int screenHeight = GetScreenHeight();
    const int screenWidth = GetScreenWidth();
    static bool flip = false;

    bounce += flip ? -0.1 : 0.1;
    y = (-1 * sin(bounce) * (range)) + screenHeight - radius - range/2;
    x += speedX;
    
    if (y >= screenHeight - radius){
        y = screenHeight - radius;
        flip = !flip;
    } else if (y <= radius){
        y = radius;
        flip = !flip;
    }

    if (x >= screenWidth - radius) {
        x = screenWidth - radius;
        speedX *= -1;
    }
    else if (x <= radius) {
        x = radius;
        speedX *= -1;
    }
    
    range -= range <= 0 ? range : range / 75;
    speedX -= speedX <= 0.05 && speedX >= -0.05 ? speedX : speedX / 50;

    std::string xtext = "X: " + std::to_string(x);
    std::string speedXtext = "X Speed: " + std::to_string(speedX);
    std::string ytext = "Y: " + std::to_string(y);
    std::string speedYtext = "Y Speed: " + std::to_string(range);
    DrawText(xtext.c_str(),      50, 5, 20, WHITE);
    DrawText(speedXtext.c_str(), 50, 30, 20, WHITE);
    DrawText(ytext.c_str(),      50, 55, 20, WHITE);
    DrawText(speedYtext.c_str(), 50, 80, 20, WHITE);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        speedX += speedX < 0 ? -distr(gen) : distr(gen);
        range += 300;
    }
}

void Ball::Draw() const
{
    DrawCircle(x, y, radius, WHITE);
}