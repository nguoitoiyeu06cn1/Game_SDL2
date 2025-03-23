#include "food.h"
#include <cstdlib> // For rand()
#include "graphics.h"

Food::Food(int screenWidth, int screenHeight) {
    randomizePosition(screenWidth, screenHeight);
}

void Food::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Food color
    drawCircle(renderer, x, y, FOOD_RADIUS); // Use the drawCircle function from graphics.cpp
}

void Food::randomizePosition(int screenWidth, int screenHeight) {
    while(true){

        x = rand() % (screenWidth - 2 * FOOD_RADIUS) + FOOD_RADIUS;
        y = rand() % (screenHeight - 2 * FOOD_RADIUS) + FOOD_RADIUS;
        if(x > 200 && y > 120){
            break;
        }
    }

}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}
