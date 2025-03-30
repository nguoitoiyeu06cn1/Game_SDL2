#include "menu.h"
#include "libra.h" // Include để sử dụng renderText và font
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

TTF_Font* menuFont = nullptr; // Font cho menu


int showLevelSelectionMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Event event;
    bool selecting = true;
    int selectedLevel = 1; // Cấp độ mặc định
    SDL_Texture* texture = nullptr;
    texture = LoadTexture("Paint/backGround.png", renderer);
    Mix_Music* intro = Mix_LoadMUS("sound/intro.mp3");
    Mix_Chunk* click = Mix_LoadWAV("sound/click_mouse.mp3");

    Mix_PlayMusic(intro, -1);
    while (selecting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return -1; // Người chơi muốn thoát game
            } else if (event.type == SDL_KEYDOWN) {
                Mix_PlayChannel(-1, click, 0);
                switch (event.key.keysym.sym) {
                    case SDLK_1: Mix_PlayChannel(-1, click, 0); selectedLevel = 1; selecting = false; Mix_HaltMusic(); break;
                    case SDLK_2: selectedLevel = 2; Mix_PlayChannel(-1, click, 0); selecting = false; Mix_HaltMusic(); break;
                    case SDLK_3: selectedLevel = 3; Mix_PlayChannel(-1, click, 0); selecting = false; Mix_HaltMusic(); break;
                    case SDLK_4: selectedLevel = 4; Mix_PlayChannel(-1, click, 0); selecting = false; Mix_HaltMusic(); break;
                    case SDLK_5: selectedLevel = 5; Mix_PlayChannel(-1, click, 0); selecting = false; Mix_HaltMusic(); break;
                    case SDLK_ESCAPE: return -1; // Thoát menu
                }
            }
        }

        // Vẽ menu


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        renderText(renderer, font, "Select Level:", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 4);
        renderText(renderer, font, "1: Level 1", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 4 + 40);
        renderText(renderer, font, "2: Level 2", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 4 + 80);
        renderText(renderer, font, "3: Level 3", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 4 + 120);
        renderText(renderer, font, "4: Level 4", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 4 + 160);
        renderText(renderer, font, "5: Level 5", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 4 + 200);
        renderText(renderer, font, "............", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 4 + 240);

        SDL_RenderPresent(renderer);
    }

    return selectedLevel;
}

