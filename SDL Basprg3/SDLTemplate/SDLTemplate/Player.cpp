#include "Player.h"
#include "Scene.h"

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
    // load texture
    texture = loadTexture("gfx/player.png");

    // initialize
    x = 100;
    y = 100;
    width = 0;
    height = 0;
    reloadTime = 8;
    currentReloadTime = 0;
    wingtipReloadTime = 16;
    currentWingtipReloadTime = 0;
    isAlive = true;

    // query the texture to set our width and height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
    // Memory management for bullets
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPositionX() > SCREEN_WIDTH)
        {
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;
            i--;
        }
    }

    if (!isAlive) return;

    if (app.keyboard[SDL_SCANCODE_W])
    {
        y -= speed;
    }

    if (app.keyboard[SDL_SCANCODE_S])
    {
        y += speed;
    }

    if (app.keyboard[SDL_SCANCODE_A])
    {
        x -= speed;
    }

    if (app.keyboard[SDL_SCANCODE_D])
    {
        x += speed;
    }

    if (app.keyboard[SDL_SCANCODE_LSHIFT])
    {
        speed = 5;
    }

    if (app.keyboard[SDL_SCANCODE_BACKSPACE])
    {
        speed = 2;
    }

    if (currentReloadTime > 0)
        currentReloadTime--;

    if (currentWingtipReloadTime > 0)
        currentWingtipReloadTime--;

    if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
    {
        SoundManager::playSound(sound);
        Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10, Side::PLAYER_SIDE);
        bullets.push_back(bullet);
        getScene()->addGameObject(bullet);

        currentReloadTime = reloadTime;
    }

    if (app.keyboard[SDL_SCANCODE_G] && currentWingtipReloadTime == 0)
    {
        SoundManager::playSound(sound);
        Bullet* bulletLeft = new Bullet(x + width, y - 2, 1, 0, 10, Side::PLAYER_SIDE);
        Bullet* bulletRight = new Bullet(x + width, y + height - 2, 1, 0, 10, Side::PLAYER_SIDE);
        bullets.push_back(bulletLeft);
        bullets.push_back(bulletRight);
        getScene()->addGameObject(bulletLeft);
        getScene()->addGameObject(bulletRight);
        bulletLeft->start();
        bulletRight->start();

        currentWingtipReloadTime = wingtipReloadTime;
    }
}

void Player::draw()
{
    if (!isAlive) return;

    blit(texture, x, y);
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
