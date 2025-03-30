#include "render.h"
#include <string>

using namespace std;

void print_lose( SDL_Renderer*& renderer, TTF_Font*& font){
    renderText(renderer, font, "Game Over!", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 60);
    renderText(renderer, font, "Do you want to play again?", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 - 30);
    renderText(renderer, font, "Choose Y: yes, N: no", SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 );
    saveHighScore(score);  //luu khi thua
    saveHighLevel(level); // luu khi thua
}
void print_level_up(SDL_Renderer*& renderer, TTF_Font*& font)
{
    renderText(renderer, font, "Game Over!", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 60);
    renderText(renderer, font, "Your score is eligible to move up to a new level. ", SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 30);
    renderText(renderer, font, "Do you want to play next level?", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 );
    renderText(renderer, font, "Choose Y: yes, N: no", SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 30);
    saveHighScore(score);  //luu khi thua
    saveHighLevel(level); // luu khi thua
}

