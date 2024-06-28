#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "PowerUp.h"
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
    float bossSpawnInterval; // Added declaration for boss spawn interval
    float currentBossSpawnTimer; // Added declaration for current boss spawn timer

    std::vector<Enemy*> spawnedEnemies;
    Boss* activeBoss; // Pointer to the active boss
    std::vector<PowerUp*> spawnedPowerUps;
    int points;
    int nextBossSpawnScore; // To keep track of the next boss spawn score

    void spawn();
    void spawnBoss(); // Function to spawn bosses
    void spawnPowerUp();
    void doSpawnLogic();
    void doCollisionLogic();
    void despawnEnemy(Enemy* enemy);
    void despawnBoss(); // Function to despawn the active boss
    void despawnPowerUp(PowerUp* powerUp);
};
