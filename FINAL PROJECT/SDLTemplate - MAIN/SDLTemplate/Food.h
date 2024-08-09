#pragma once
#include "SDL.h"
#include "defs.h"

class Food
{
public:
    Food();
    void spawn();
    void draw();
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
    SDL_Color color;
};
