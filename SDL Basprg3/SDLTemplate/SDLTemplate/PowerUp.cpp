#include "PowerUp.h"
#include "Scene.h"
#include "common.h"
#include "draw.h"

PowerUp::PowerUp()
{
    texture = nullptr;
    width = 0;
    height = 0;
    speed = 2;
}

PowerUp::~PowerUp()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void PowerUp::start()
{
    texture = loadTexture("gfx/points.png");
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::update()
{
    y += speed; // Move downward


    if (y > SCREEN_HEIGHT)
    {
        setActive(false); // Deactivate or handle despawning
    }
}

void PowerUp::draw()
{
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderCopy(app.renderer, texture, NULL, &rect);
}

void PowerUp::setPosition(int xPos, int yPos)
{
    x = xPos;
    y = yPos;
}

int PowerUp::getPositionX()
{
    return x;
}

int PowerUp::getPositionY()
{
    return y;
}

int PowerUp::getWidth()
{
    return width;
}

int PowerUp::getHeight()
{
    return height;
}

void PowerUp::setActive(bool active)
{
    isActive = active;
}

bool PowerUp::checkCollision(int playerX, int playerY, int playerWidth, int playerHeight)
{
    if (x < playerX + playerWidth &&
        x + width > playerX &&
        y < playerY + playerHeight &&
        y + height > playerY)
    {
        return true;
    }
    return false;
}
