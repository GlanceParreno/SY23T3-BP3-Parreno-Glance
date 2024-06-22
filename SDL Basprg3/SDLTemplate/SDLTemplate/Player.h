#pragma once

#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
    ~Player();
    void start() override;
    void update() override;
    void draw() override;

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool getIsAlive();
    void doDeath();
    void upgradeFiringPattern();

private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    int x;
    int y;
    int width;
    int height;
    int speed = 5; // Increase speed for vertical movement
    float reloadTime;
    float currentReloadTime;
    float wingtipReloadTime;
    float currentWingtipReloadTime;
    std::vector<Bullet*> bullets;
    bool isAlive;
    int firingPatternLevel;
};
