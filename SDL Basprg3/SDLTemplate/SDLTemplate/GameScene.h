#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

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
	Player* player;
	Enemy* enemy;


	//Spawner
	float spawnTime;
	float currentSpawnTimer;
	vector<Enemy*> spawnedEnemies;
	void spawn();
	
};

