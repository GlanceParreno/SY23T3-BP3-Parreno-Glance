#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"


using namespace std;

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();
    void start();
    void draw();
    void update();
private:
    SDL_Texture* texture;
    Player* player;
    Enemy* enemy;
    SDL_Texture* explosionTexture;
    bool isExplosionActive;
    int explosionX;
    int explosionY;
    int explosionDuration;

    // Spawner
    float spawnTime;
    float currentSpawnTimer;
    vector<Enemy*> spawnedEnemies;

    void spawn();


    void doSpawnLogic();
    void doCollisionLogic();
    void despawnEnemy(Enemy* enemy);

    int points;

};