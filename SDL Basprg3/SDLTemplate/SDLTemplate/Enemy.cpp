#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
    texture = loadTexture("gfx/enemy.png");
    directionX = 0; // Set directionX to 0 to stop horizontal movement
    directionY = 1; // Set directionY to 1 to move downwards
    width = 0;
    height = 0;
    speed = 2;
    reloadTime = 60;
    currentReloadTime = 0;
    directionChangeTime = (rand() % 300) + 180; // direction change time of 3-8 sec
    currentDirectionChangeTime = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
    y += directionY * speed; // Vertical movement (moving downwards)

    if (currentDirectionChangeTime > 0)
        currentDirectionChangeTime--;

    if (currentDirectionChangeTime == 0)
    {
        directionY = 1; // Ensure enemies only move downward
        currentDirectionChangeTime = directionChangeTime;
    }

    if (currentReloadTime > 0)
        currentReloadTime--;

    if (currentReloadTime == 0)
    {
        float dx = -1;
        float dy = 0;

        calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

        SoundManager::playSound(sound);
        Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
        bullets.push_back(bullet);
        getScene()->addGameObject(bullet);

        currentReloadTime = reloadTime;
    }

    // Check if enemy moves off the bottom of the screen
    if (y > SCREEN_HEIGHT)
    {
        // Handle despawning or resetting position if needed
        y = -height - 10; // Reset above the top of the screen
    }

    // Manage bullet memory
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPositionX() < 0)
        {
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;
            i--;
        }
    }
}

void Enemy::draw()
{
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderCopyEx(app.renderer, texture, NULL, &rect, 270, NULL, SDL_FLIP_NONE); 
}

void Enemy::setPlayerTarget(Player* player)
{
    playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
    x = xPos;
    y = yPos;
}

int Enemy::getPositionX()
{
    return x;
}

int Enemy::getPositionY()
{
    return y;
}

int Enemy::getWidth()
{
    return width;
}

int Enemy::getHeight()
{
    return height;
}
