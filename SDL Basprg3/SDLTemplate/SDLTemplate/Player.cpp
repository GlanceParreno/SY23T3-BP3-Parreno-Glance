#include "Player.h"
#include "Scene.h"
#include <SDL.h>

Player::~Player()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        delete bullets[i];
    }
    bullets.clear();
}

void Player::start()
{
    texture = loadTexture("gfx/player.png");
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT - height - 50;
    width = 0;
    height = 0;
    reloadTime = 8;
    currentReloadTime = 0;
    wingtipReloadTime = 16;
    currentWingtipReloadTime = 0;
    isAlive = true;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
    // Memory management for bullets
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPositionY() < 0)
        {
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;
            i--;
        }
    }

    if (!isAlive) return;

    if (app.keyboard[SDL_SCANCODE_A])
    {
        x -= speed;
    }

    if (app.keyboard[SDL_SCANCODE_D])
    {
        x += speed;
    }

    if (app.keyboard[SDL_SCANCODE_W])
    {
        y -= speed;
    }

    if (app.keyboard[SDL_SCANCODE_S])
    {
        y += speed;
    }

    if (currentReloadTime > 0)
        currentReloadTime--;

    if (currentWingtipReloadTime > 0)
        currentWingtipReloadTime--;

    if (app.keyboard[SDL_SCANCODE_LSHIFT])
    {
        speed = 8; // Adjust speed for vertical movement
    }

    if (app.keyboard[SDL_SCANCODE_BACKSPACE])
    {
        speed = 5; // Default speed
    }

    if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
    {
        SoundManager::playSound(sound);
        Bullet* bullet = new Bullet(x - 2 + width / 2, y - height, 0, -1, 10, Side::PLAYER_SIDE); // Adjust bullet position and direction
        bullets.push_back(bullet);
        getScene()->addGameObject(bullet);

        currentReloadTime = reloadTime;
    }

    /*
    * if (app.keyboard[SDL_SCANCODE_G] && currentWingtipReloadTime == 0)
    {
        SoundManager::playSound(sound);
        Bullet* bulletLeft = new Bullet(x - 2, y - height, 0, -1, 10, Side::PLAYER_SIDE); // Adjust bullet positions and directions
        Bullet* bulletRight = new Bullet(x + width - 2, y - height, 0, -1, 10, Side::PLAYER_SIDE);
        bullets.push_back(bulletLeft);
        bullets.push_back(bulletRight);
        getScene()->addGameObject(bulletLeft);
        getScene()->addGameObject(bulletRight);
        bulletLeft->start();
        bulletRight->start();

        currentWingtipReloadTime = wingtipReloadTime;
    }
    */
}

void Player::draw()
{
    if (!isAlive) return;

    SDL_Rect rect = { x, y, width, height };
    SDL_RenderCopyEx(app.renderer, texture, NULL, &rect, 270, NULL, SDL_FLIP_NONE); // Rotate texture 90 degrees clockwise
}

int Player::getPositionX()
{
    return x;
}

int Player::getPositionY()
{
    return y;
}

int Player::getWidth()
{
    return width;
}

int Player::getHeight()
{
    return height;
}

bool Player::getIsAlive()
{
    return isAlive;
}

void Player::doDeath()
{
    isAlive = false;
}

void Player::upgradeFiringPattern() 
{
    
    firingPatternLevel++; 
    
}
