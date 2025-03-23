#include "AIsnake.h"
#include <cstdlib> // Need rand()
#include <cmath> // Need some functions

AIsnake :: AIsnake(int startX, int startY, int initialDirection) : currentDirection(initialDirection)
{
    segments = {{startX - 200, startY - 200},
                {startX - 250, startY - 200},
                {startX - 250, startY - 200}
    };
    switch (initialDirection)
    {
        case 0: velX = 0; velY = -4; break; //up
        case 1: velX = 0; velY = 4; break; //down
        case 2: velX = -4; velY = 0; break; //left
        case 3: velX = 4; velY = 0; break; //right

    }
}
void AIsnake::update(int playerSnakeX, int playerSnakeY)
{
    // random direction change
    if(rand() % 100 < 5) // 5% chance to change direction
    {
        currentDirection = rand() % 4; // choose a new random direction
        switch (currentDirection)
        {
            case 0: velX = 0; velY = -4; break; //up
            case 1: velX = 0; velY = 4; break; //down
            case 2: velX = -4; velY = 0; break; //left
            case 3: velX = 4; velY = 0; break; //right
        }
    }

    SnakeSegment newHead = {segments[0].x + (int)velX, segments[0].y + (int)velY};

    // wrap around logic
    if(newHead.y < 0) newHead.y = 600;
    if(newHead.y > 600) newHead.y = 0;
    if(newHead.x < 0) newHead.x = 800;
    if(newHead.x > 800) newHead.x = 0;

    segments.insert(segments.begin(), newHead);
    segments.pop_back();

}
void AIsnake::draw(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);// AI snake yellow
    for(const auto& segment: segments)
    {
        drawCircle(renderer, segment.x, segment.y, 10);
    }
}

bool AIsnake::checkCollision(const Snake& playerSnake)
{
    SnakeSegment aiHead = segments[0];
    vector <SnakeSegment> playerSegments = playerSnake.getSegments();
    for(const auto& playerSegment : playerSegments)
    {
        double distance = hypot(aiHead.x - playerSegment.x, aiHead.y - playerSegment.y);
        if(distance < 20) return true; // collision happened
    }
    return false;
}

bool AIsnake::checkSelfCollision()
{
    SnakeSegment head = segments[0];
    for(size_t i = 1; i < segments.size(); ++i)
    {
        if(head.x == segments[i].x && head.y == segments[i].y)
        {
            return true;
        }
    }
    return false;
}

vector <SnakeSegment> AIsnake::getSegments() const
{
    return segments;
}
