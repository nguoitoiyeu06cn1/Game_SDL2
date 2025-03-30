#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "graphics.h" // ve hinh tron cho thuc an va cac thu kha
#include <SDL.h> // Needed for SDL_Renderer
using namespace std;

const int CIRCLE_RADIUS = 10;
const int BASE_SPEED = 4;

struct SnakeSegment {
    int x, y;
};

class Snake {
public:
    Snake(int startX, int startY);
    void update(double velX, double velY);
    void draw(SDL_Renderer* renderer);
    void grow();
    bool checkCollisions(const vector<SnakeSegment>& otherSnakeSegments);// kiem tra va cham voi ran kha
    bool checkCollision(int foodX, int foodY, int foodRadius);// kiem tra va cham voi thuc an
    bool checkSelfCollision();// kiem tra va cham voi ban than
    void reset(int startX, int startY);
    SnakeSegment getHead() const;
    vector<SnakeSegment> getSegments() const;

private:
    vector<SnakeSegment> segments;
    double speedMultiplier = 1.0;

};

#endif
