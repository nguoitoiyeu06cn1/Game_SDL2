#include "libra.h"


int main(int argc, char * argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    TTF_Font* font = nullptr;

    if (!init(window, renderer, font)) return -1;
    texture = LoadTexture("Paint/backGround.png", renderer);

    Mix_Chunk* eatSound = Mix_LoadWAV("sound/eat_food.mp3");
    if (eatSound == nullptr) {
        cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    Mix_Music* bgMusic = Mix_LoadMUS("sound/ontiva_E2NG2X2.mp3");
    Mix_Chunk* endMusic = Mix_LoadWAV("sound/game_over1.mp3");

    if (bgMusic == nullptr) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
    }
    if (endMusic == nullptr) {
        cout << "Failed to load endMusic music! SDL_mixer Error: " << Mix_GetError() << endl;
    }


    srand(time(0));
    bool running = true;
    SDL_Event event;
    bool useMouseControl = false;

    Snake snake(SCREEN_WIDTH, SCREEN_HEIGHT);
    Food food(SCREEN_WIDTH, SCREEN_HEIGHT);
    AIsnake aiSnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);

    double velX = 4, velY = 0;

    bool startGame = true;
    bool gameOver = false;
    bool paused = false;
    int highScore = loadHighScore();
    int highLevel = loadLevel();

    // Hiển thị menu chọn cấp độ
    int selectedLevel = showLevelSelectionMenu(renderer, font);
    int level = selectedLevel;
    if (selectedLevel == -1) {
        close(window, renderer, font, texture);
        return 0; // Người chơi muốn thoát game
    }
    Mix_PlayMusic(bgMusic, -1);
    int score = 10 * selectedLevel;

    // Khởi tạo số lượng rắn AI dựa trên cấp độ đã chọn
    createAIsnakes(selectedLevel, SCREEN_WIDTH, SCREEN_HEIGHT);
    aiSnake.update(snake.getHead().x, snake.getHead().y);

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
                    case SDLK_SPACE:
                        paused = true; Mix_HaltMusic(); break;
                    case SDLK_r:
                        aiSnakes.clear();
                        createAIsnakes(selectedLevel, SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo lại rắn AI theo cấp độ đã chọn
                        aiSnake.update(snake.getHead().x, snake.getHead().y);
                        gameOver = false;
                        score = 0;
                        count_score = 0;
                        level = 0;
                        snake = Snake(SCREEN_WIDTH, SCREEN_HEIGHT);
                        food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT);
                        velX = 4;
                        velY = 0;
                        useMouseControl = false;
                        aiSnake = AIsnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);
                        paused = false;
                        break;
                }
            } else if (event.type == SDL_MOUSEMOTION && !gameOver && !paused) {
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
        if (!gameOver && !paused ) {
            snake.update(velX, velY);

            for (auto& aiSnake : aiSnakes) {
                aiSnake.update(snake.getHead().x, snake.getHead().y);
                if(snake.checkCollisions(aiSnake.getSegments()))
                {
                    gameOver = true;
                }
            }

            // if (snake.checkSelfCollision()) gameOver = true;

            if (snake.checkCollision(food.getX(), food.getY(), 8)) {
                Mix_PlayChannel(-1, eatSound, 0);
                snake.grow();
                food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT);
                score++;
                count_score++;
                if (count_score >= 10) {
                    count_score -= 10;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        snake.draw(renderer);

        for ( auto& aiSnake : aiSnakes) {
            aiSnake.draw(renderer);
        }

        food.draw(renderer);

        renderText(renderer, font, "Score: " + to_string(score), 20, 20);
        renderText(renderer, font, "High Score: " + to_string(highScore), 20, 50);
        renderText(renderer, font, "Level: " + to_string(level), 20, 80);
        renderText(renderer, font, "High Level:" + to_string(highLevel), 20, 110);

        if (paused) {

            renderText(renderer, font, "Paused", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2);
            SDL_RenderPresent(renderer);

            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                }
                if (event.type == SDL_KEYDOWN){
                    switch(event.key.keysym.sym){
                        case SDLK_SPACE:
                            paused = false; Mix_PlayMusic(bgMusic, -1); break;
                        case SDLK_l:
                            if(increase_level(score, level) == true){
                                aiSnakes.clear(); // clear het cac ran ai cu
                                createAIsnakes(level + 1, SCREEN_WIDTH, SCREEN_HEIGHT); //
                                Mix_PlayMusic(bgMusic, -1);
                                gameOver = false;
                                score = 20 + (level-1) * 10;
                                level += 1;
                                snake = Snake(SCREEN_WIDTH, SCREEN_HEIGHT); //
                                food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT); //
                                velX = 4;
                                velY = 0;
                                useMouseControl = false;
                                aiSnake = AIsnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);
                                paused = false;
                            }
                            else continue;
                            break;
                    }
                }
            }
        }

        bool level_up = increase_level(score, level);

        if (gameOver) {
            Mix_HaltMusic();
            level = selectedLevel;
            if(increase_level(score, level) == true){

                Mix_PlayChannel(-1, endMusic, 0);
                print_level_up(renderer, font);
                SDL_RenderPresent(renderer);
                aiSnakes.clear(); //
                createAIsnakes(level + 1, SCREEN_WIDTH, SCREEN_HEIGHT); // tao ran ai moi

                SDL_Event event;
                bool waiting = true;
                while (waiting) {
                    if (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            running = false;
                            waiting = false;
                            break;
                        } else if (event.type == SDL_KEYDOWN) {
                            Mix_HaltMusic();
                            switch (event.key.keysym.sym){
                                case SDLK_y:
                                    Mix_PlayMusic(bgMusic, -1);
                                    gameOver = false;
                                    score = 20 + (level-1) * 10;
                                    count_score = 0;
                                    level += 1;
                                    snake = Snake(SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo snake mới
                                    food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo thức ăn mới
                                    velX = 4;
                                    velY = 0;
                                    useMouseControl = false;
                                    aiSnake = AIsnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);
                                    paused = false;
                                break;
                                case SDLK_n:
                                    running = false;
                                break;
                            }
                                waiting = false; // Người dùng nhấn phím, tiếp tục game
                                break;
                            }
                    }
                        SDL_Delay(10); // Giảm tải cho CPU
                        hasLeveledUp = false;
                }

        }
        else if(level_up == false){
            Mix_PlayChannel(-1, endMusic, 0);
            print_lose(renderer, font);
            SDL_RenderPresent(renderer);
            aiSnakes.clear();
            bool waiting = true;
            while(waiting){
                if(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        running = false;
                        waiting = false;
                }
                    else if (event.type == SDL_KEYDOWN){
                        Mix_HaltMusic();
                        switch (event.key.keysym.sym){
                        case SDLK_y:
                            gameOver = false;
                            Mix_PlayMusic(bgMusic, -1);
                            score = 0;
                            level = 0;
                            snake = Snake(SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo snake mới
                            food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo thức ăn mới
                            velX = 4;
                            velY = 0;
                            useMouseControl = false;
                            createAIsnakes(selectedLevel, SCREEN_WIDTH, SCREEN_HEIGHT); //Tạo lại rắn theo level đã chọn
                            aiSnake.update(snake.getHead().x, snake.getHead().y);
                            aiSnake = AIsnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);
                            paused = false;
                        break;
                        case SDLK_n:
                            running = false;
                            break;
                        }
                            waiting = false; // Người dùng nhấn phím, tiếp tục game
                    }
                }
            }
        }
    }

        SDL_RenderPresent(renderer);
        SDL_Delay(8);
    }
    close(window, renderer, font, texture);
    return 0;
}
