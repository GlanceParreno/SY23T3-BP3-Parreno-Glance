#include "GameScene.h"
#include "Food.h"
#include "common.h"

GameScene::GameScene() : points(0), gameOver(false), promptRestart(false)
{
    player.start();
    food.spawn(); // Initialize the food object at a random position
}

GameScene::~GameScene() {}

void GameScene::start()
{
    initFonts();
}

void GameScene::update()
{
    if (gameOver)
    {
        if (app.keyboard[SDL_SCANCODE_Y])
        {
            restart(); // Restart the game if 'Y' is pressed
        }
        else if (app.keyboard[SDL_SCANCODE_N])
        {
            SDL_Log("Exiting game...");
            exit(0); // Close the application
        }
        return;
    }

    player.update();

    if (player.isAlive())
    {
        // Check if the player has collided with the food
        if (player.getX() == food.getX() && player.getY() == food.getY())
        {
            points++;
            player.increaseSize(); // Increase player size
            SDL_Log("Food eaten! Player size increased.");
            food.spawn(); // Respawn food at a new location after being eaten
        }
    }
    else
    {
        gameOver = true; // Set game over when player is not alive
        promptRestart = true; // Prompt player to restart
    }
}

void GameScene::draw()
{
    drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

    if (player.isAlive())
    {
        player.draw();
    }
    food.draw(); // Draw the food on the screen

    if (gameOver)
    {
        drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 255, 0, 0, TEXT_CENTER, "GAME OVER");
        drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20, 255, 255, 255, TEXT_CENTER, "Restart? (Y/N)");
    }
}

void GameScene::restart()
{
    player.start(); // Reset player state
    food.spawn(); // Spawn food at a new location
    points = 0; // Reset points
    gameOver = false; // Reset game over state
    promptRestart = false; // Reset prompt restart flag
}
