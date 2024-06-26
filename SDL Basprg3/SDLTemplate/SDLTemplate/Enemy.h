#pragma once

#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>
#include "util.h"

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();
    void start() override;
    void update() override;
    void draw() override;
    void setPlayerTarget(Player* player);
    void setPosition(int xPos, int yPos);

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    Player* playerTarget;
    int x;
    int y;
    float directionX;
    float directionY;
    int width;
    int height;
    int speed;
    float reloadTime;
    float currentReloadTime;
    float wingtipReloadTime;
    float currentWingtipReloadTime;
    float directionChangeTime;
    float currentDirectionChangeTime;
    std::vector<Bullet*> bullets;
};
