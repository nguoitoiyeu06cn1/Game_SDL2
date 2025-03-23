#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
using namespace std;


// Constants (consider putting these in a config file if you want them easily changeable)
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


bool init(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font);
void close(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* texture);
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const string& text, int x, int y);
SDL_Texture* LoadTexture(const string& filePath, SDL_Renderer* renderer);


#endif
