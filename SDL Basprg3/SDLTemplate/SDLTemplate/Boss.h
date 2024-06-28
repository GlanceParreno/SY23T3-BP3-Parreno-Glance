#pragma once

#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>
#include "util.h"

class Boss : public GameObject
{
public:
    Boss();
    ~Boss();
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
    bool isDoubleFire; // Flag to indicate if boss is in double fire mode
    int currentFireModeTimer; // Timer to control the fire mode switching
    int fireModeSwitchInterval; // Interval at which the boss switches fire modes
};
