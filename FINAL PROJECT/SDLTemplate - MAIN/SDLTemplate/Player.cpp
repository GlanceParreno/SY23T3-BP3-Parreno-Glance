#include "Player.h"
#include "app.h"

extern App app;

Player::Player() : color({ 255, 255, 255, 255 }), alive(true), directionX(1), directionY(0) {}

void Player::start()
{
    body.clear();
    SDL_Rect initialSegment = { 0, 0, 20, 20 }; // Initial segment size
    body.push_back(initialSegment);
    color = { 255, 255, 255, 255 }; // White color
    alive = true;
    directionX = 1; // Initial direction (moving right)
    directionY = 0;
}

void Player::update()
{
    if (!alive)
        return; // Skip update if player is not alive

    // Move first
    move();

    // Check for collisions
    checkCollisions();
}

void Player::draw()
{
    if (!alive)
        return; // Skip drawing if player is not alive

    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);
    for (const auto& segment : body)
    {
        SDL_RenderFillRect(app.renderer, &segment);
    }
}

int Player::getX() const
{
    return body[0].x;
}

int Player::getY() const
{
    return body[0].y;
}

void Player::increaseSize()
{
    // Add a new segment at the end of the body
    SDL_Rect newSegment = body.back(); // Duplicate the last segment
    body.push_back(newSegment);
}

void Player::move()
{
    // Move all segments
    if (body.empty())
        return;

    // Save the previous position of the head
    SDL_Rect prevPosition = body[0];

    // Move the body segments
    for (size_t i = 1; i < body.size(); ++i)
    {
        SDL_Rect temp = body[i];
        body[i] = prevPosition;
        prevPosition = temp;
    }

    // Move the head segment
    body[0].x += directionX * 20; // Move in the X direction
    body[0].y += directionY * 20; // Move in the Y direction

    // Ensure the player stays within the screen bounds
    if (body[0].x < 0 || body[0].x + body[0].w > SCREEN_WIDTH ||
        body[0].y < 0 || body[0].y + body[0].h > SCREEN_HEIGHT)
    {
        alive = false; // Set player to dead if it collides with the wall
    }

    // Update direction based on keyboard input
    if (app.keyboard[SDL_SCANCODE_W] && directionY == 0)
    {
        directionX = 0;
        directionY = -1;
    }
    if (app.keyboard[SDL_SCANCODE_S] && directionY == 0)
    {
        directionX = 0;
        directionY = 1;
    }
    if (app.keyboard[SDL_SCANCODE_A] && directionX == 0)
    {
        directionX = -1;
        directionY = 0;
    }
    if (app.keyboard[SDL_SCANCODE_D] && directionX == 0)
    {
        directionX = 1;
        directionY = 0;
    }
}

void Player::checkCollisions()
{
    // Check self-collision
    for (size_t i = 1; i < body.size(); ++i)
    {
        if (body[0].x == body[i].x && body[0].y == body[i].y)
        {
            alive = false; // Set player to dead if it collides with itself
            break;
        }
    }
}
