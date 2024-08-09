#include "Food.h"
#include "app.h"
#include <cstdlib>

extern App app;

Food::Food() : x(0), y(0), color({ 255, 0, 0, 255 }) {}

void Food::spawn()
{
    x = (rand() % (SCREEN_WIDTH / 20)) * 20;
    y = (rand() % (SCREEN_HEIGHT / 20)) * 20;
}

void Food::draw()
{
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, 20, 20 };
    SDL_RenderFillRect(app.renderer, &rect);
}
