#include "GameScene.h"
#include <SDL.h>

GameScene::GameScene()
{
    player = new Player();
    this->addGameObject(player);
    points = 0;
    nextBossSpawnScore = 3; // Initialize next boss spawn score
    activeBoss = nullptr; // No active boss at the start

}

GameScene::~GameScene()
{
    delete player;
    for (auto enemy : spawnedEnemies)
    {
        delete enemy;
    }
    spawnedEnemies.clear();

    for (auto powerUp : spawnedPowerUps)
    {
        delete powerUp;
    }
    if (activeBoss)
    {
        delete activeBoss;
    }
    spawnedPowerUps.clear();
}

void GameScene::start()
{
    Scene::start();
    texture = loadTexture("gfx/background.png");
    explosionTexture = loadTexture("gfx/Bang.png");
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
    SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(app.renderer, texture, NULL, &destRect);
    Scene::draw();

    if (isExplosionActive)
    {
        blit(explosionTexture, explosionX, explosionY);
    }

    drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

    if (!player->getIsAlive())
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
            isExplosionActive = false;
        }
    }

    Scene::update();
    doSpawnLogic();
    doCollisionLogic();

    // Check if player score is a multiple of 3 to spawn boss
    if (points > 0 && points % 3 == 0 && activeBoss == nullptr)
    {
        spawnBoss();
    }
}

void GameScene::spawn()
{
    Enemy* enemy = new Enemy();
    this->addGameObject(enemy);
    enemy->setPlayerTarget(player);

    // Set enemy position just above the top of the screen
    int spawnX = rand() % (SCREEN_WIDTH - enemy->getWidth()); // Random X position within screen width
    int spawnY = -enemy->getHeight(); // Spawn just above the top of the screen
    enemy->setPosition(spawnX, spawnY);

    spawnedEnemies.push_back(enemy);
    currentSpawnTimer = spawnTime;
}

void GameScene::spawnBoss()
{
    activeBoss = new Boss();
    this->addGameObject(activeBoss);
    activeBoss->setPlayerTarget(player);

    int spawnX = rand() % (SCREEN_WIDTH - activeBoss->getWidth());
    int spawnY = -activeBoss->getHeight();
    activeBoss->setPosition(spawnX, spawnY);
}

void GameScene::spawnPowerUp()
{
    PowerUp* powerUp = new PowerUp();
    this->addGameObject(powerUp);
    powerUp->start();

    // Randomize X position within the screen width for power-up
    int spawnX = rand() % (SCREEN_WIDTH - powerUp->getWidth());
    int spawnY = -powerUp->getHeight(); // Spawn just above the top of the screen
    powerUp->setPosition(spawnX, spawnY);

    spawnedPowerUps.push_back(powerUp);
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

void GameScene::despawnBoss()
{
    if (activeBoss != nullptr)
    {
        delete activeBoss;
        activeBoss = nullptr;
    }
}

void GameScene::despawnPowerUp(PowerUp* powerUp)
{
    int index = -1;
    for (int i = 0; i < spawnedPowerUps.size(); i++)
    {
        if (powerUp == spawnedPowerUps[i])
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
        delete powerUp;
    }
}

void GameScene::doSpawnLogic()
{
    if (currentSpawnTimer > 0)
        currentSpawnTimer--;

    if (currentSpawnTimer <= 0 && activeBoss == nullptr) // Only spawn enemies if no boss is active
    {
        for (int i = 0; i < 3; i++)
        {
            spawn();
        }
        currentSpawnTimer = spawnTime;
    }

    for (int i = 0; i < spawnedEnemies.size(); i++)
    {
        if (spawnedEnemies[i]->getPositionX() < 0)
        {
            despawnEnemy(spawnedEnemies[i]);
            i--;
        }
    }

    for (int i = 0; i < spawnedPowerUps.size(); i++)
    {
        if (spawnedPowerUps[i]->getPositionX() < 0)
        {
            despawnPowerUp(spawnedPowerUps[i]);
            i--;
        }
    }

    if (activeBoss != nullptr && activeBoss->getPositionX() < 0)
    {
        despawnBoss();
    }
}

void GameScene::doCollisionLogic()
{
    // Collision logic between player and power-ups
    for (int i = 0; i < spawnedPowerUps.size(); i++)
    {
        PowerUp* powerUp = spawnedPowerUps[i];

        if (powerUp->checkCollision(player->getPositionX(), player->getPositionY(),
            player->getWidth(), player->getHeight()))
        {
            // Handle power-up collection here
            despawnPowerUp(powerUp);
            points += 10;
            break;
        }
    }

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
                    player->doDeath();
                    break;
                }
            }
            else if (bullet->getSide() == Side::PLAYER_SIDE)
            {
                // Check collision with enemies (including boss)
                for (int j = 0; j < spawnedEnemies.size(); j++)
                {
                    Enemy* enemy = spawnedEnemies[j];

                    int collision = checkCollision(enemy->getPositionX(), enemy->getPositionY(),
                        enemy->getWidth(), enemy->getHeight(),
                        bullet->getPositionX(), bullet->getPositionY(),
                        bullet->getWidth(), bullet->getHeight());

                    if (collision == 1)
                    {
                        despawnEnemy(enemy);
                        isExplosionActive = true;
                        explosionX = enemy->getPositionX();
                        explosionY = enemy->getPositionY();
                        explosionDuration = 60;

                        points++;
                        break;
                    }
                }

                // Check collision with active boss
                if (activeBoss != nullptr)
                {
                    int collision = checkCollision(activeBoss->getPositionX(), activeBoss->getPositionY(),
                        activeBoss->getWidth(), activeBoss->getHeight(),
                        bullet->getPositionX(), bullet->getPositionY(),
                        bullet->getWidth(), bullet->getHeight());

                    if (collision == 1)
                    {
                        despawnBoss();
                        isExplosionActive = true;
                        explosionX = activeBoss->getPositionX();
                        explosionY = activeBoss->getPositionY();
                        explosionDuration = 60;
                        points += 10;
                        break;
                    }
                }
            }
        }
    }
}
