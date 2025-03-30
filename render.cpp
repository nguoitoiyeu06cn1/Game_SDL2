#include "render.h"
#include <string>

using namespace std;

/*if(IMG_Init(IMG_INIT_PNG) == 0){
    cout << "ERROR" << IMG_GetError() << endl;
}*/

void print_lose( SDL_Renderer*& renderer, TTF_Font*& font){
    renderText(renderer, font, "Game Over!", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2);
    renderText(renderer, font, "Do you want to play again?", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 30);
    renderText(renderer, font, "Choose Y: yes, N: no", SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 60);
    saveHighScore(score);  //Save high score when game is over
    saveHighLevel(level); // Save high level when game is over
}
void print_level_up(SDL_Renderer*& renderer, TTF_Font*& font)
{
    renderText(renderer, font, "Game Over!", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2);
    renderText(renderer, font, "Your score is eligible to move up to a new level. ", SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 0);
    renderText(renderer, font, "Do you want to play next level?", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 30);
    renderText(renderer, font, "Choose Y: yes, N: no", SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 60);
    saveHighScore(score);  //Save high score when game is over
    saveHighLevel(level); // Save high level when game is over
}

