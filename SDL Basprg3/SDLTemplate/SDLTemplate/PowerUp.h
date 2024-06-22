#pragma once

#include "GameObject.h"
#include <SDL.h>

class PowerUp : public GameObject
{
public:
    PowerUp();
    ~PowerUp();
    void start() override;
    void update() override;
    void draw() override;

    void setPosition(int xPos, int yPos);

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    void setActive(bool active);
    bool checkCollision(int playerX, int playerY, int playerWidth, int playerHeight);

private:
    SDL_Texture* texture;
    int x, y;
    int width, height;
    int speed;
    bool isActive;
};

