#include "GameScene.h"
#include <SDL.h>


GameScene::GameScene()
{
    // Register and add game objects in constructor
    player = new Player();
    this->addGameObject(player);

    points = 0;
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
    texture = loadTexture("gfx/background.png");
    explosionTexture = loadTexture("gfx/Bang.png");
    // Initialize any scene logic here
    initFonts();
    currentSpawnTimer = 300;
    spawnTime = 300;

    for (int i = 0; i < 3; i++)
    {
        spawn();
    }
}

void GameScene::draw()
{
    // Calculate the destination rectangle to cover the entire screen
    SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // Render the background texture
    SDL_RenderCopy(app.renderer, texture, NULL, &destRect);
    Scene::draw();

    // Draw explosion if active
    if (isExplosionActive)
    {
        // Blit explosion sprite at explosion position
        blit(explosionTexture, explosionX, explosionY);
    }

    drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

    if (player->getIsAlive() == false)
    {
        drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME IS OVER!");
    }
}

void GameScene::update()
{
    // Update explosion duration
    if (isExplosionActive)
    {
        explosionDuration--;
        if (explosionDuration <= 0)
        {
            // Deactivate explosion
            isExplosionActive = true;
        }
    }
    Scene::update();
    doSpawnLogic();
    doCollisionLogic();
}

void GameScene::doSpawnLogic()
{
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
            despawnEnemy(spawnedEnemies[i]);
            i--;
        }
    }
}

void GameScene::doCollisionLogic()
{
    for (int i = 0; i < objects.size(); i++)
    {
        Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

        if (bullet != NULL)
        {
            if (bullet->getSide() == Side::ENEMY_SIDE)
            {
                int collision = checkCollision(player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                    bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());

                if (collision == 1)
                {
                    // Player is hit by an enemy bullet
                    player->doDeath();
                    break;
                }
            }
            else if (bullet->getSide() == Side::PLAYER_SIDE)
            {
                for (int j = 0; j < spawnedEnemies.size(); j++)
                {
                    Enemy* currentEnemy = spawnedEnemies[j];

                    int collision = checkCollision(currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
                        bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());

                    if (collision == 1)
                    {
                        // Enemy is hit by a player bullet
                        despawnEnemy(currentEnemy);

                        // Activate explosion at enemy's position
                        isExplosionActive = true;
                        explosionX = currentEnemy->getPositionX();
                        explosionY = currentEnemy->getPositionY();
                        explosionDuration = 60; // Adjust the duration as needed

                        points++;
                        break;
                    }
                }
            }
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

void GameScene::despawnEnemy(Enemy* enemy)
{
    int index = -1;
    for (int i = 0; i < spawnedEnemies.size(); i++)
    {
        if (enemy == spawnedEnemies[i])
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        spawnedEnemies.erase(spawnedEnemies.begin() + index);
        delete enemy;
    }
}