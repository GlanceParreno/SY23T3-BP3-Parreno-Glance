#pragma once
#include <SDL.h>
#include <vector>

class Player
{
public:
    Player();
    void start();
    void update();
    void draw();

    int getX() const; // Getter for X coordinate
    int getY() const; // Getter for Y coordinate

    bool isAlive() const { return alive; } // Check if player is alive
    void increaseSize(); // Method to increase player size


private:
    std::vector<SDL_Rect> body; // Player body segments
    SDL_Color color;
    bool alive; // Player alive status
    int directionX; // Direction of movement in X
    int directionY; // Direction of movement in Y

    void move(); // Move player segments
    void checkCollisions(); // Check for collisions
};
