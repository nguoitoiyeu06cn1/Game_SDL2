#ifndef FOOD_H
#define FOOD_H

#include "SDL.h" // Needed for SDL_Renderer
#include "graphics.h" // For drawCircle

const int FOOD_RADIUS = 8;

class Food {
public:
    Food(int screenWidth, int screenHeight);
    void draw(SDL_Renderer* renderer);// ve
    void randomizePosition(int screenWidth, int screenHeight);// random vi tri cho thuc an
    int getX() const;
    int getY() const;
    int x, y;

};

#endif
