#include "Bullet.h"

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{
    this->x = positionX;
    this->y = positionY;
    this->directionX = directionX;
    this->directionY = directionY;
    this->speed = speed;
    this->side = side;
}

void Bullet::start()
{
    width = 0;
    height = 0;

    if (side == Side::PLAYER_SIDE)
    {
        texture = loadTexture("gfx/playerBullet.png");
    }
    else
    {
        texture = loadTexture("gfx/alienBullet.png");
    }

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
    x += directionX * speed;
    y += directionY * speed;
}

void Bullet::draw()
{
    // Calculate rotation angle in degrees
    double angle = 270.0; // 270 degrees clockwise

    // Calculate the center of rotation (assuming the texture's center)
    int centerX = width / 2;
    int centerY = height / 2;

    // Set the rotation point
    SDL_Point pivot = { centerX, centerY };

    // Render the rotated texture
    SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), width, height };
    SDL_RenderCopyEx(app.renderer, texture, NULL, &rect, angle, &pivot, SDL_FLIP_NONE);
}

int Bullet::getPositionX()
{
    return x;
}

int Bullet::getPositionY()
{
    return y;
}

int Bullet::getWidth()
{
    return width;
}

int Bullet::getHeight()
{
    return height;
}

Side Bullet::getSide()
{
    return side;
}
