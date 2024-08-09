#include "main.h"
#include "GameScene.h"
#include "Food.h"

Food food;  // Declare the food object globally

static void capFrameRate(long* then, float* remainder);

int main(int argc, char* argv[])
{
    srand(time(NULL));
    long then;
    float remainder;

    // Allocate memory for the App struct
    memset(&app, 0, sizeof(App));
    app.textureTail = &app.textureHead;

    // Initialize SDL and open a window
    initSDL();
    // On application exit, call cleanup function
    atexit(cleanup);

    then = SDL_GetTicks();
    remainder = 0;

    // Initialize GameScene or any first scene you want here
    GameScene* scene = new GameScene();

    // Initialize food
    food.spawn();

    // Framework code
    Scene::setActiveScene(scene);

    // Main game loop
    while (true)
    {
        Uint32 currentTime = SDL_GetTicks();
        app.deltaTime = currentTime - then;
        then = currentTime;

        prepareScene();
        doInput();

        Scene::getActiveScene()->update();
        Scene::getActiveScene()->draw();

        // Draw the food
        food.draw();

        presentScene();

        capFrameRate(&then, &remainder);
    }
    delete scene;

    return 0;
}

static void capFrameRate(long* then, float* remainder)
{
    long wait, frameTime;

    wait = 16 + *remainder;

    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if (wait < 1)
    {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;

    *then = SDL_GetTicks();
}
