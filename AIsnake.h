#ifndef AISNAKE_H_INCLUDED
#define AISNAKE_H_INCLUDED

#include <vector>
#include "snake.h"
#include "graphics.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class AIsnake
{
public:
    AIsnake(int startX, int startY, int initialDirection); // the same vector gradient
    void update(int playerSnakeX, int playerSnakeY); // Information player position
    void draw(SDL_Renderer * renderer);
    bool checkCollision(const Snake& playerSnake); // Collision with PlayerSnake
    bool checkSelfCollision();
    vector <SnakeSegment> getSegments() const; // Need to check collision with obstancle
private:
    vector <SnakeSegment> segments;
    double velX, velY;
    int currentDirection; //0:up 1:down 2:left 3:right

};
#endif // AISNAKE_H_INCLUDED
