#include "GameScene.h"

GameScene::GameScene()
{
    // Register and add game objects in constructor
    player = new Player();
    this->addGameObject(player);
}

GameScene::~GameScene()
{
    delete player;
    for (auto enemy : spawnedEnemies)
    {
        delete enemy;
    }
    spawnedEnemies.clear();
}

void GameScene::start()
{
    Scene::start();
    // Initialize any scene logic here
    currentSpawnTimer = 300;
    spawnTime = 300;

    for (int i = 0; i < 3; i++)
    {
        spawn();
    }
}

void GameScene::draw()
{
    Scene::draw();
}

void GameScene::update()
{
    Scene::update();

    if (currentSpawnTimer > 0)
        currentSpawnTimer--;

    if (currentSpawnTimer <= 0)
    {
        for (int i = 0; i < 3; i++)
        {
            spawn();
        }
        currentSpawnTimer = spawnTime;
    }

    // Memory management for enemies
    for (int i = 0; i < spawnedEnemies.size(); i++)
    {
        if (spawnedEnemies[i]->getPositionX() < 0)  
        {
            Enemy* enemyToErase = spawnedEnemies[i];
            spawnedEnemies.erase(spawnedEnemies.begin() + i);
            delete enemyToErase;
            i--;
        }
    }
}

void GameScene::spawn()
{
    Enemy* enemy = new Enemy();
    this->addGameObject(enemy);
    enemy->setPlayerTarget(player);

    enemy->setPosition(SCREEN_WIDTH + 100, 300 + (rand() % 300)); // Spawning beyond the right side of the screen
    spawnedEnemies.push_back(enemy);
    currentSpawnTimer = spawnTime;
}
