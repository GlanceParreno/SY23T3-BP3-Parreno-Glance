#include "Boss.h"
#include "Scene.h"

// FOR SAKE OF TESTING I MADE IT ONLY SCORE OF 3 SO BOSS CAN SPAWN FOR DEBUGGING
// FOR SAKE OF TESTING I MADE IT ONLY SCORE OF 3 SO BOSS CAN SPAWN FOR DEBUGGING
// FOR SAKE OF TESTING I MADE IT ONLY SCORE OF 3 SO BOSS CAN SPAWN FOR DEBUGGING
// FOR SAKE OF TESTING I MADE IT ONLY SCORE OF 3 SO BOSS CAN SPAWN FOR DEBUGGING
// FOR SAKE OF TESTING I MADE IT ONLY SCORE OF 3 SO BOSS CAN SPAWN FOR DEBUGGING
// FOR SAKE OF TESTING I MADE IT ONLY SCORE OF 3 SO BOSS CAN SPAWN FOR DEBUGGING

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::start()
{
    texture = loadTexture("gfx/Boss.png");
    directionX = 0; // Set directionX to 0 to stop horizontal movement
    directionY = 1; // Set directionY to 1 to move downwards
    width = 0;
    height = 0;
    speed = 1; // Bosses move slower than regular enemies
    reloadTime = 15; // Initial reload time
    currentReloadTime = 0;
    directionChangeTime = (rand() % 300) + 180; // direction change time of 3-8 sec
    currentDirectionChangeTime = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

    isDoubleFire = false; // Start with single fire mode
    currentFireModeTimer = 120; // Start the timer for fire mode switch
    fireModeSwitchInterval = 120; // Switch fire mode every 2 seconds (120 frames)
}

void Boss::update()
{
    // Vertical movement (moving downwards)
    y += directionY * speed;

    // Horizontal movement logic every 2 seconds
    if (currentDirectionChangeTime > 0)
    {
        currentDirectionChangeTime--;

        // Move horizontally every 2 seconds
        if (currentDirectionChangeTime == 0)
        {
            // Toggle movement direction every 2 seconds
            if (directionX == 0)
            {
                directionX = (rand() % 2 == 0) ? 1 : -1;  // Randomly choose left or right
            }
            else
            {
                directionX = -directionX;  // Reverse current direction
            }
        }
    }
    else
    {
        // Reset direction change time when it reaches 0
        directionY = 1; // Ensure bosses only move downward
        currentDirectionChangeTime = directionChangeTime;
    }

    // Apply horizontal movement
    x += directionX * speed;

    // Reload and fire logic
    if (currentReloadTime > 0)
        currentReloadTime--;

    if (currentReloadTime == 0)
    {
        float dx = -1;
        float dy = 0;

        calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

        SoundManager::playSound(sound);

        if (isDoubleFire)
        {
            // Fire 2 bullets on each side
            float dx2 = dx;
            float dy2 = dy;
            dx2 += 0.2f; // Offset for the second bullet on the right side
            dy2 += 0.2f; // Offset for the second bullet on the right side

            Bullet* bullet1 = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
            bullets.push_back(bullet1);
            getScene()->addGameObject(bullet1);

            Bullet* bullet2 = new Bullet(x + width, y - 2 + height / 2, dx2, dy2, 10, Side::ENEMY_SIDE);
            bullets.push_back(bullet2);
            getScene()->addGameObject(bullet2);
        }
        else
        {
            // Fire 1 bullet
            Bullet* bullet1 = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
            bullets.push_back(bullet1);
            getScene()->addGameObject(bullet1);
        }

        currentReloadTime = reloadTime;
    }

    // Check if boss moves off the bottom of the screen
    if (y > SCREEN_HEIGHT)
    {
        // Handle despawning or resetting position if needed
        y = -height - 10; // Reset above the top of the screen
        x = rand() % (SCREEN_WIDTH - width); // Randomize X position within screen width
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

    // Toggle double fire every 2 seconds
    currentFireModeTimer--;
    if (currentFireModeTimer <= 0)
    {
        isDoubleFire = !isDoubleFire; // Toggle between single and double fire
        currentFireModeTimer = fireModeSwitchInterval; // Reset timer

        // Adjust reload time based on fire mode
        if (isDoubleFire)
        {
            reloadTime = 15; // Double fire mode reload time
        }
        else
        {
            reloadTime = 30; // Single fire mode reload time
        }
    }
}


void Boss::draw()
{
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderCopyEx(app.renderer, texture, NULL, &rect, 270, NULL, SDL_FLIP_NONE);
}

void Boss::setPlayerTarget(Player* player)
{
    playerTarget = player;
}

void Boss::setPosition(int xPos, int yPos)
{
    x = xPos;
    y = yPos;
}

int Boss::getPositionX()
{
    if (this == nullptr)
    {
        return 0;
    }
    return x;
}

int Boss::getPositionY()
{
    if (this == nullptr)
    {
        return 0;
    }
    return y;
}

int Boss::getWidth()
{
    return width;
}

int Boss::getHeight()
{
    return height;
}
