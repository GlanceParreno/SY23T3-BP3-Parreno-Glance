#pragma once
#include "Scene.h"
#include "Player.h"
#include "Food.h"
#include "text.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void start() override;
    void update() override;
    void draw() override;

private:
    Player player;
    Food food; // Food object to handle food-related logic

    int points;
    bool gameOver; // Flag to track game over state
    bool promptRestart; // Flag to prompt the player to restart
    void restart(); // Method to restart the game
};
