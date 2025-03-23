#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "utils.h"
#include "level.h"

void print_lose( SDL_Renderer*& renderer, TTF_Font*& font);
void print_level_up( SDL_Renderer*& renderer, TTF_Font*& font);


#endif // RENDER_H_INCLUDED
