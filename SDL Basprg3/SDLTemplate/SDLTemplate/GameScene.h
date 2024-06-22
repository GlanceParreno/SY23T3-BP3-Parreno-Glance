#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h" // Include PowerUp header
#include <vector>
#include "text.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();
    void start() override;
    void draw() override;
    void update() override;

private:
    SDL_Texture* texture;
    Player* player;
    SDL_Texture* explosionTexture;
    bool isExplosionActive;
    int explosionX;
    int explosionY;
    int explosionDuration;

    float spawnTime;
    float currentSpawnTimer;
    std::vector<Enemy*> spawnedEnemies;
    std::vector<PowerUp*> spawnedPowerUps; // Vector to store spawned power-ups
    int points;

    void spawn();
    void spawnPowerUp(); // Function to spawn power-ups
    void doSpawnLogic();
    void doCollisionLogic();
    void despawnEnemy(Enemy* enemy);
    void despawnPowerUp(PowerUp* powerUp); // Function to despawn power-ups
};

