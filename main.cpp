#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "graphics.h"
#include "snake.h"
#include "food.h"
#include "utils.h"
#include "AIsnake.h"

int main(int argc, char * argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    if (!init(window, renderer, font)) return -1;

    srand(time(0));
    bool running = true;
    SDL_Event event;
    bool useMouseControl = false;

    Snake snake(SCREEN_WIDTH, SCREEN_HEIGHT); //Snake class object instantiation
    Food food(SCREEN_WIDTH, SCREEN_HEIGHT);   //Food class object instantiation
    AIsnake aiSnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);

    double velX = 4, velY = 0;
    int score = 0;
    int count_score = 0;
    int highScore = loadHighScore();
    bool gameOver = false;
    bool Continue = true;

    while(Continue){
        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN && !gameOver) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:    velX = 0; velY = -4 ; useMouseControl = false; break;
                        case SDLK_DOWN:  velX = 0; velY = 4; useMouseControl = false; break;
                        case SDLK_LEFT:  velX = -4; velY = 0; useMouseControl = false; break;
                        case SDLK_RIGHT: velX = 4; velY = 0; useMouseControl = false; break;
                    }
                } else if (event.type == SDL_MOUSEMOTION && !gameOver) {
                    useMouseControl = true;
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    SnakeSegment head = snake.getHead();
                    double diffX = mouseX - head.x;
                    double diffY = mouseY - head.y;
                    double length = sqrt(diffX * diffX + diffY * diffY);
                    if (length > 0) {
                        velX = (diffX / length) * 4;
                        velY = (diffY / length) * 4;
                    }
                }
            }
    
            if (!gameOver) {
    
                snake.update(velX, velY);
                aiSnake.update(snake.getHead().x, snake.getHead().y);
    
                if (snake.checkSelfCollision()) gameOver = true;
    
                if (snake.checkCollision(food.getX(), food.getY(), 8)) {
                    snake.grow();
                    food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT);
                    score++;
                    count_score++;
                    if (count_score >= 10) {
                        count_score -= 10;
                    }
                }
    
                /*if(snake.checkCollision(aiSnake.getSegments()))
                {
                    gameOver = true;
                }*/
    
    
            }
    
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
            SDL_RenderClear(renderer);
    
            snake.draw(renderer);
            aiSnake.draw(renderer);
            food.draw(renderer);
    
            renderText(renderer, font, "Score: " + std::to_string(score), 20, 20);
            renderText(renderer, font, "High Score: " + std::to_string(highScore), 20, 50);

            
            if (gameOver) {
              renderText(renderer, font, "Game Over!", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2);
              renderText(renderer, font, "Do you want to play again ?", SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 + 10); 
              saveHighScore(score);  //Save high score when game is over
                
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(8);
        }
    }

    close(window, renderer, font);
    return 0;
}
